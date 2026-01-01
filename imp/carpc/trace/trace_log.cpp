#include "carpc/trace/functions.h"
#include "carpc/trace/trace_event.h"
#include "carpc/trace/trace_runtime.h"
#include "carpc/trace/trace_log.h"



using namespace carpc::trace;



void TraceLog::trace( const char* fmt, ... )
{
   va_list args;
   va_start( args, fmt );
   log( eTraceLevel::Trace, fmt, args );
   va_end( args );
}

void TraceLog::debug( const char* fmt, ... )
{
   va_list args;
   va_start( args, fmt );
   log( eTraceLevel::Debug, fmt, args );
   va_end( args );
}

void TraceLog::info( const char* fmt, ... )
{
   va_list args;
   va_start( args, fmt );
   log( eTraceLevel::Info, fmt, args );
   va_end( args );
}

void TraceLog::warning( const char* fmt, ... )
{
   va_list args;
   va_start( args, fmt );
   log( eTraceLevel::Warn, fmt, args );
   va_end( args );
}

void TraceLog::error( const char* fmt, ... )
{
   va_list args;
   va_start( args, fmt );
   log( eTraceLevel::Error, fmt, args );
   va_end( args );
}

void TraceLog::critical( const char* fmt, ... )
{
   va_list args;
   va_start( args, fmt );
   log( eTraceLevel::Critical, fmt, args );
   va_end( args );
}

void TraceLog::log( eTraceLevel level, const char* fmt, ... )
{
   va_list args;
   va_start( args, fmt );
   log( level, fmt, args );
   va_end( args );
}

void TraceLog::log( eTraceLevel level, const char* fmt, va_list args )
{
   TraceEvent* event = TraceRuntime::acquire_event( );
   if( event == nullptr )
      return;
   event->timestamp_ns( functions::now_ns( ) );
   event->thread_id( functions::tid( ) );
   event->phase( eTracePhase::Instant );
   event->level( level );
   event->message( fmt, args );

   TraceRuntime::emit( event );
}
