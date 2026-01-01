#include "carpc/trace/functions.h"
#include "carpc/trace/trace_ring_buffer_spsc.h"

#include "carpc/trace/trace_debug.h"



using namespace carpc::trace;



TraceRingBufferSPSC::TraceRingBufferSPSC( size_t capacity )
   : m_capacity( capacity )
{
   CARPC_TRACE_DEBUG( );
   m_buffer = new const TraceEvent* [ m_capacity ];
}

TraceRingBufferSPSC::~TraceRingBufferSPSC( )
{
   CARPC_TRACE_DEBUG( );
   delete[] m_buffer;
}

bool TraceRingBufferSPSC::push( const TraceEvent* event )
{
   CARPC_TRACE_DEBUG( "-> push: %p", event );

   const size_t head = m_head.load( std::memory_order_relaxed );
   const size_t next = ( head + 1 ) % m_capacity;

   if( next == m_tail.load( std::memory_order_acquire ) ) 
   {
      CARPC_TRACE_DEBUG( "buffer full" );
      ++m_push.error;
      return false; // full
   }
   ++m_push.success;

   m_buffer[ head ] = event;
   m_head.store( next, std::memory_order_release );

   CARPC_TRACE_DEBUG( "<- pushed: %p", event );
   return true;
}

const TraceEvent* TraceRingBufferSPSC::pop( )
{
   CARPC_TRACE_DEBUG( "-> pop" );

   const size_t tail = m_tail.load( std::memory_order_relaxed );

   if( tail == m_head.load( std::memory_order_acquire ) )
   {
      CARPC_TRACE_DEBUG( "buffer empty" );
      ++m_pop.error;
      return nullptr; // empty
   }
   ++m_pop.success;

   const TraceEvent* event = m_buffer[ tail ];
   const size_t next = ( tail + 1 ) % m_capacity;
   m_tail.store( next, std::memory_order_release );

   CARPC_TRACE_DEBUG( "<- poped: %p", event );
   return event;
}
