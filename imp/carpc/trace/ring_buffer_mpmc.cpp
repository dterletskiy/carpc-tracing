#include "carpc/trace/functions.h"
#include "ring_buffer_mpmc.h"

#include "carpc/trace/debug.h"



using namespace carpc::trace;



RingBufferMPMC::RingBufferMPMC( size_t capacity )
   : IRingBuffer( capacity )
   , m_buffer( new Cell[ capacity ] )
   , m_head( 0 )
   , m_tail( 0 )
{
   CARPC_TRACE_DEBUG( );
   for( size_t i = 0; i < m_capacity; ++i )
   {
      m_buffer[ i ].sequence.store( i, std::memory_order_relaxed );
   }
}

RingBufferMPMC::~RingBufferMPMC( )
{
   CARPC_TRACE_DEBUG( );
   delete[] m_buffer;
}

bool RingBufferMPMC::push( const Event* event )
{
   CARPC_TRACE_DEBUG( "-> push: %p", event );

   size_t pos = m_head.load( std::memory_order_relaxed );

   for( ;; )
   {
      Cell& cell = m_buffer[ pos % m_capacity ];
      size_t seq = cell.sequence.load( std::memory_order_acquire );
      intptr_t dif = ( intptr_t )seq - ( intptr_t )pos;

      if( dif == 0 )
      {
         if( m_head.compare_exchange_weak(
               pos,
               pos + 1,
               std::memory_order_relaxed ) )
         {
            cell.data = event;
            cell.sequence.store( pos + 1, std::memory_order_release );
            ++m_push.success;

            CARPC_TRACE_DEBUG( "<- pushed: %p", event );
            return true;
         }
      }
      else if( dif < 0 )
      {
         ++m_push.error;
         CARPC_TRACE_DEBUG( "buffer full" );
         return false; // buffer full
      }
      else
      {
         pos = m_head.load( std::memory_order_relaxed );
      }
   }
}

const Event* RingBufferMPMC::pop( )
{
   CARPC_TRACE_DEBUG( "-> pop" );

   size_t pos = m_tail.load( std::memory_order_relaxed );

   for( ;; )
   {
      Cell& cell = m_buffer[ pos % m_capacity ];
      size_t seq = cell.sequence.load( std::memory_order_acquire );
      intptr_t dif = ( intptr_t )seq - ( intptr_t )( pos + 1 );

      if( dif == 0 )
      {
         if( m_tail.compare_exchange_weak(
               pos,
               pos + 1,
               std::memory_order_relaxed ) )
         {
            const Event* event = cell.data;
            cell.sequence.store(
               pos + m_capacity,
               std::memory_order_release );
            ++m_pop.success;

            CARPC_TRACE_DEBUG( "<- poped: %p", event );
            return event;
         }
      }
      else if( dif < 0 )
      {
         ++m_pop.error;
         CARPC_TRACE_DEBUG( "buffer empty" );
         return nullptr; // buffer empty
      }
      else
      {
         pos = m_tail.load( std::memory_order_relaxed );
      }
   }
}
