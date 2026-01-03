#include <algorithm>
#include <chrono>
#include <vector>
#include <queue>
#include <atomic>
#include <thread>

#include "thread_context.h"
#include "thread_registry.h"
#include "event_pool.h"
#include "carpc/trace/futex.h"
#include "carpc/trace/sink.h"
#include "carpc/trace/runtime.h"

#include "carpc/trace/debug.h"



using namespace carpc::trace;



ISink*             s_sink    = nullptr;
std::atomic< bool >     s_running = false;
std::thread             s_thread;
os::Futex               s_futex;
EventPool          s_trace_event_pool;
eLevel             s_min_level;



void Runtime::start( ISink* sink )
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
   s_thread = std::thread( &Runtime::consumer_loop );
}

void Runtime::stop( )
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

void Runtime::emit( const Event* event )
{
   CARPC_TRACE_DEBUG( "-> runtime try emit: %s", event->message( ) );
   if( not s_running.load( std::memory_order_acquire ) )
      return;

   if( event->level( ) < s_min_level )
      return;

   CARPC_TRACE_DEBUG( "-> runtime emit: %s", event->message( ) );
   ThreadContext::current( ).buffer.push( event ); // SPSC, lock-free
   {
      s_futex.wake( );
   }
   CARPC_TRACE_DEBUG( "<- runtime emit: %s", event->message( ) );
}

Event* Runtime::acquire_event( )
{
   if( not s_running.load( std::memory_order_acquire ) )
      return nullptr;

   return s_trace_event_pool.acquire( );
}

void Runtime::release_event( const Event* event )
{
   s_trace_event_pool.release( event );
}

void Runtime::min_level( eLevel level )
{
   s_min_level = level;
}

eLevel Runtime::min_level( )
{
   return s_min_level;
}

void Runtime::consumer_loop( )
{
   CARPC_TRACE_DEBUG( "consumer thread enter" );

   const Event* event = nullptr;

   while( s_running.load( std::memory_order_acquire ) )
   {
      CARPC_TRACE_DEBUG( "-> consumer thread loop" );
      for( auto* ctx : ThreadRegistry::contexts( ) )
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
   for( auto* ctx : ThreadRegistry::contexts( ) )
   {
      while( nullptr != ( event = ctx->buffer.pop( ) ) )
      {
         CARPC_TRACE_DEBUG( "consumer thread emit" );
         s_sink->emit( event );
      }
   }

   CARPC_TRACE_DEBUG( "consumer thread exit" );
}

void Runtime::consumer_loop_sort( )
{
   CARPC_TRACE_DEBUG( "consumer thread enter" );

   struct HeapEntry
   {
      const Event* event;
      ThreadContext* ctx;
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

   const Event* event = nullptr;

   while( s_running.load( std::memory_order_acquire ) )
   {
      // CARPC_TRACE_DEBUG("consumer process");
      for( auto* ctx : ThreadRegistry::contexts( ) )
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

      const Event* next = top.ctx->buffer.pop( );
      if( next != nullptr )
         heap.push( { next, top.ctx } );
   }

   // final drain
   for( auto* ctx : ThreadRegistry::contexts( ) )
   {
      const Event* e = nullptr;
      while( nullptr != ( e = ctx->buffer.pop( ) ) )
         s_sink->emit( e );
   }

   CARPC_TRACE_DEBUG( "consumer thread exit" );
}
