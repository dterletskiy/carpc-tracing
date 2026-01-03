#include "thread_context.h"
#include "thread_registry.h"

#include "carpc/trace/debug.h"



using namespace carpc::trace;



ThreadRegistry::CONTEXTS    ThreadRegistry::s_contexts;
std::mutex                       ThreadRegistry::s_mutex;



ThreadContext* ThreadRegistry::create_context( )
{
   auto* ctx = new ThreadContext( );
   CARPC_TRACE_DEBUG( "%p", ctx );
   std::lock_guard< std::mutex > lock( s_mutex );
   s_contexts.push_back( ctx );
   return ctx;
}

const ThreadRegistry::CONTEXTS ThreadRegistry::contexts( )
{
   CARPC_TRACE_DEBUG( );
   std::lock_guard< std::mutex > lock( s_mutex );
   return s_contexts;
}
