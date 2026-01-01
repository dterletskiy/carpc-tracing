#include "carpc/trace/functions.h"
#include "carpc/trace/trace_event.h"
#include "carpc/trace/trace_runtime.h"
#include "carpc/trace/trace_scope.h"



using namespace carpc::trace;



TraceScope::TraceScope( const char* message )
   : m_message( message )
{
   TraceEvent* event = TraceRuntime::acquire_event( );
   if(event == nullptr)
      return;
   event->timestamp_ns( functions::now_ns( ) );
   event->thread_id( functions::tid( ) );
   event->phase( eTracePhase::Begin );
   event->message( m_message );

   TraceRuntime::emit( event );
}

TraceScope::~TraceScope( )
{
   TraceEvent* event = TraceRuntime::acquire_event( );
   if(event == nullptr)
      return;
   event->timestamp_ns( functions::now_ns( ) );
   event->thread_id( functions::tid( ) );
   event->phase( eTracePhase::End );
   event->message( m_message );

   TraceRuntime::emit( event );
}
