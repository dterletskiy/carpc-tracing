#include "carpc/trace/trace_runtime.h"
#include "carpc/trace/trace_sink.h"



using namespace carpc::trace;



void ITraceSink::emit( const TraceEvent* event )
{
   emit_priv( event );

   TraceRuntime::release_event( event );
}