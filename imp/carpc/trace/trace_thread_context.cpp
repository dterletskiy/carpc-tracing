#include "trace_thread_registry.h"
#include "trace_thread_context.h"

#include "carpc/trace/trace_debug.h"



using namespace carpc::trace;



struct ThreadContextGuard
{
   ThreadContextGuard( );
   ~ThreadContextGuard( );
};



thread_local TraceThreadContext* g_trace_tls_ctx = nullptr;
thread_local ThreadContextGuard  g_trace_tls_guard;



TraceThreadContext::TraceThreadContext( )
{
   CARPC_TRACE_DEBUG( );
}

TraceThreadContext::~TraceThreadContext( )
{
   CARPC_TRACE_DEBUG( );
}

TraceThreadContext& TraceThreadContext::current( )
{
   CARPC_TRACE_DEBUG( );
   (void)g_trace_tls_guard;
   if( !g_trace_tls_ctx )
   {
      g_trace_tls_ctx = TraceThreadRegistry::create_context( );
   }
   return *g_trace_tls_ctx;
}



ThreadContextGuard::ThreadContextGuard( )
{
   CARPC_TRACE_DEBUG( );
}

ThreadContextGuard::~ThreadContextGuard( )
{
   CARPC_TRACE_DEBUG( );
   if( g_trace_tls_ctx )
   {
      g_trace_tls_ctx->alive.store( false, std::memory_order_release );
   }
}
