#include <iostream>

#include "trace_event_pool.h"

#include "carpc/trace/trace_debug.h"



using namespace carpc::trace;



TraceEventPool::TraceEventPool( size_t capacity )
   : m_capacity( capacity )
{
   mp_storage = new TraceEvent[ m_capacity ];
   // mp_used = new bool[ m_capacity ]{ };
   mp_used = new std::atomic< bool >[ m_capacity ];
   for( size_t i = 0; i < m_capacity; ++i )
   {
      mp_used[ i ].store( false, std::memory_order_relaxed );
   }
}

TraceEventPool::~TraceEventPool( )
{
   delete[] mp_storage;
   delete[] mp_used;
}

// TraceEvent* TraceEventPool::acquire( )
// {
//    for( size_t i = 0; i < m_capacity; ++i )
//    {
//       const size_t idx = ( m_head + i ) % m_capacity;

//       if( !mp_used[ idx ] )
//       {
//          CARPC_TRACE_DEBUG( "acquired index: %p", idx );
//          mp_used[ idx ] = true;
//          m_head = ( idx + 1 ) % m_capacity;
//          return &mp_storage[ idx ];
//       }
//    }

//    CARPC_TRACE_DEBUG( "acquire error" );
//    return nullptr; // pool exhausted
// }

// void TraceEventPool::release( const TraceEvent* event )
// {
//    const ptrdiff_t idx = event - mp_storage;

//    if( idx >= 0 && static_cast< size_t >( idx ) < m_capacity )
//    {
//       mp_used[ idx ] = false;
//       CARPC_TRACE_DEBUG( "released index: %p", idx );
//    }
//    else
//    {
//       CARPC_TRACE_DEBUG( "release error" );
//    }
// }

TraceEvent* TraceEventPool::acquire( )
{
   const size_t head = m_head.load( std::memory_order_relaxed );

   for( size_t i = 0; i < m_capacity; ++i )
   {
      const size_t idx = ( head + i ) % m_capacity;

      bool expected = false;

      if( mp_used[ idx ].compare_exchange_strong(
             expected,
             true,
             std::memory_order_acquire,
             std::memory_order_relaxed ) )
      {
         m_head.store( ( idx + 1 ) % m_capacity,
                       std::memory_order_relaxed );

         // CARPC_TRACE_DEBUG( "acquired index: %zu", idx );
         return &mp_storage[ idx ];
      }
   }

   CARPC_TRACE_DEBUG( "acquire error" );
   return nullptr;
}

void TraceEventPool::release( const TraceEvent* event )
{
   const ptrdiff_t idx = event - mp_storage;

   if( idx >= 0 && static_cast< size_t >( idx ) < m_capacity )
   {
      mp_used[ idx ].store( false, std::memory_order_release );
      // CARPC_TRACE_DEBUG( "released index: %zu", static_cast< size_t >( idx ) );
   }
   else
   {
      CARPC_TRACE_DEBUG( "release error" );
   }
}
