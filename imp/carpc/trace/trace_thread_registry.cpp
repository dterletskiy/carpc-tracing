#include "trace_thread_context.h"
#include "trace_thread_registry.h"

#include "carpc/trace/trace_debug.h"



using namespace carpc::trace;



TraceThreadRegistry::CONTEXTS    TraceThreadRegistry::s_contexts;
std::mutex                       TraceThreadRegistry::s_mutex;



TraceThreadContext* TraceThreadRegistry::create_context( )
{
   auto* ctx = new TraceThreadContext( );
   CARPC_TRACE_DEBUG( "%p", ctx );
   std::lock_guard< std::mutex > lock( s_mutex );
   s_contexts.push_back( ctx );
   return ctx;
}

const TraceThreadRegistry::CONTEXTS TraceThreadRegistry::contexts( )
{
   CARPC_TRACE_DEBUG( );
   std::lock_guard< std::mutex > lock( s_mutex );
   return s_contexts;
}
