#include "thread_registry.h"
#include "thread_context.h"

#include "carpc/trace/debug.h"



using namespace carpc::trace;



struct ThreadContextGuard
{
   ThreadContextGuard( );
   ~ThreadContextGuard( );
};



thread_local ThreadContext* g_trace_tls_ctx = nullptr;
thread_local ThreadContextGuard  g_trace_tls_guard;



ThreadContext::ThreadContext( )
{
   CARPC_TRACE_DEBUG( );
}

ThreadContext::~ThreadContext( )
{
   CARPC_TRACE_DEBUG( );
}

ThreadContext& ThreadContext::current( )
{
   CARPC_TRACE_DEBUG( );
   (void)g_trace_tls_guard;
   if( !g_trace_tls_ctx )
   {
      g_trace_tls_ctx = ThreadRegistry::create_context( );
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
