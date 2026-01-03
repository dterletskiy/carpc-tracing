#include "carpc/trace/functions.h"
#include "ring_buffer_mutex.h"

#include "carpc/trace/debug.h"



using namespace carpc::trace;



RingBufferMutex::RingBufferMutex( size_t capacity )
   : m_capacity( capacity )
{
   CARPC_TRACE_DEBUG( );
   m_buffer = new const Event* [ m_capacity ];
}

RingBufferMutex::~RingBufferMutex( )
{
   CARPC_TRACE_DEBUG( );
   delete[] m_buffer;
}

bool RingBufferMutex::push( const Event* event )
{
   CARPC_TRACE_DEBUG( "-> push: %p", event );

   std::lock_guard< std::mutex > lock( m_mutex );

   const size_t next = ( m_head + 1 ) % m_capacity;
   if( next == m_tail ) 
   {
      CARPC_TRACE_DEBUG( "buffer full" );
      ++m_push.error;
      return false; // full
   }
   ++m_push.success;

   m_buffer[ m_head ] = event;
   m_head = next;

   CARPC_TRACE_DEBUG( "<- pushed: %p", event );
   return true;
}

const Event* RingBufferMutex::pop( )
{
   CARPC_TRACE_DEBUG( "-> pop" );

   std::lock_guard< std::mutex > lock( m_mutex );

   if( m_tail == m_head )
   {
      CARPC_TRACE_DEBUG( "buffer empty" );
      ++m_pop.error;
      return nullptr; // empty
   }
   ++m_pop.success;

   const Event* event = m_buffer[ m_tail ];
   m_tail = ( m_tail + 1 ) % m_capacity;

   CARPC_TRACE_DEBUG( "<- poped: %p", event );
   return event;
}
