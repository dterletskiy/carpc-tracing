#include <algorithm>
#include <chrono>
#include <vector>
#include <queue>
#include <atomic>
#include <thread>

#include "trace_thread_context.h"
#include "trace_thread_registry.h"
#include "trace_event_pool.h"
#include "carpc/trace/futex.h"
#include "carpc/trace/trace_sink.h"
#include "carpc/trace/trace_runtime.h"

#include "carpc/trace/trace_debug.h"



using namespace carpc::trace;



ITraceSink*             s_sink    = nullptr;
std::atomic< bool >     s_running = false;
std::thread             s_thread;
os::Futex               s_futex;
TraceEventPool          s_trace_event_pool;
eTraceLevel             s_min_level;



void TraceRuntime::start( ITraceSink* sink )
{
   CARPC_TRACE_DEBUG( );

   bool expected = false;
   if( !s_running.compare_exchange_strong(
         expected, true, std::memory_order_acq_rel
      ) )
   {
      // runtime already running
      return;
   }

   s_sink = sink;
   s_thread = std::thread( &TraceRuntime::consumer_loop );
}

void TraceRuntime::stop( )
{
   CARPC_TRACE_DEBUG( );

   bool expected = true;
   if( !s_running.compare_exchange_strong(
         expected, false, std::memory_order_acq_rel
      ) )
   {
      // runtime already running
      return;
   }

   // wakeup consumer for graceful shutdown
   s_futex.wake( );

   if( s_thread.joinable( ) )
   {
      s_thread.join( );
   }
}

void TraceRuntime::emit( const TraceEvent* event )
{
   CARPC_TRACE_DEBUG( "-> runtime try emit: %s", event->message( ) );
   if( not s_running.load( std::memory_order_acquire ) )
      return;

   if( event->level( ) < s_min_level )
      return;

   CARPC_TRACE_DEBUG( "-> runtime emit: %s", event->message( ) );
   TraceThreadContext::current( ).buffer.push( event ); // SPSC, lock-free
   {
      s_futex.wake( );
   }
   CARPC_TRACE_DEBUG( "<- runtime emit: %s", event->message( ) );
}

TraceEvent* TraceRuntime::acquire_event( )
{
   if( not s_running.load( std::memory_order_acquire ) )
      return nullptr;

   return s_trace_event_pool.acquire( );
}

void TraceRuntime::release_event( const TraceEvent* event )
{
   s_trace_event_pool.release( event );
}

void TraceRuntime::min_level( eTraceLevel level )
{
   s_min_level = level;
}

eTraceLevel TraceRuntime::min_level( )
{
   return s_min_level;
}

void TraceRuntime::consumer_loop( )
{
   CARPC_TRACE_DEBUG( "consumer thread enter" );

   const TraceEvent* event = nullptr;

   while( s_running.load( std::memory_order_acquire ) )
   {
      CARPC_TRACE_DEBUG( "-> consumer thread loop" );
      for( auto* ctx : TraceThreadRegistry::contexts( ) )
      {
         CARPC_TRACE_DEBUG( "consumer thread context processing: %p", ctx );
         while( nullptr != ( event = ctx->buffer.pop( ) ) )
         {
            CARPC_TRACE_DEBUG( "consumer thread emit: %p", event );
            s_sink->emit( event );
         }
      }
      CARPC_TRACE_DEBUG( "consumer thread emit finished: %p", event );

      if( nullptr == event )
      {
         CARPC_TRACE_DEBUG( "consumer thread wait" );
         s_futex.wait( );
         s_futex.reset( );
      }
      CARPC_TRACE_DEBUG( "<- consumer thread loop" );
   }

   // final drain
   for( auto* ctx : TraceThreadRegistry::contexts( ) )
   {
      while( nullptr != ( event = ctx->buffer.pop( ) ) )
      {
         CARPC_TRACE_DEBUG( "consumer thread emit" );
         s_sink->emit( event );
      }
   }

   CARPC_TRACE_DEBUG( "consumer thread exit" );
}

void TraceRuntime::consumer_loop_sort( )
{
   CARPC_TRACE_DEBUG( "consumer thread enter" );

   struct HeapEntry
   {
      const TraceEvent* event;
      TraceThreadContext* ctx;
   };

   auto cmp = [ ]( const HeapEntry& a, const HeapEntry& b )
   {
      if( !a.event && !b.event )
      {
         CARPC_TRACE_DEBUG("compare error" );
      }
      return a.event->timestamp_ns( ) > b.event->timestamp_ns( );
   };
   std::priority_queue< HeapEntry, std::vector< HeapEntry >, decltype(cmp) >
      heap(cmp);

   const TraceEvent* event = nullptr;

   while( s_running.load( std::memory_order_acquire ) )
   {
      // CARPC_TRACE_DEBUG("consumer process");
      for( auto* ctx : TraceThreadRegistry::contexts( ) )
      {
         if( nullptr != ( event = ctx->buffer.pop( ) ) )
            heap.push( { event, ctx } );
      }

      if( heap.empty( ) )
      {
         // CARPC_TRACE_DEBUG("consumer wait");
         s_futex.wait( );
         s_futex.reset( );
         continue;
      }

      // Обрабатываем минимальное событие
      HeapEntry top = heap.top( );
      heap.pop( );
      s_sink->emit( top.event );

      const TraceEvent* next = top.ctx->buffer.pop( );
      if( next != nullptr )
         heap.push( { next, top.ctx } );
   }

   // final drain
   for( auto* ctx : TraceThreadRegistry::contexts( ) )
   {
      const TraceEvent* e = nullptr;
      while( nullptr != ( e = ctx->buffer.pop( ) ) )
         s_sink->emit( e );
   }

   CARPC_TRACE_DEBUG( "consumer thread exit" );
}
