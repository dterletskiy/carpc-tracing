#include "carpc/trace/functions.h"
#include "carpc/trace/event.h"
#include "carpc/trace/runtime.h"
#include "carpc/trace/log.h"



using namespace carpc::trace;



void Log::trace( const char* fmt, ... )
{
   va_list args;
   va_start( args, fmt );
   log( eLevel::Trace, fmt, args );
   va_end( args );
}

void Log::debug( const char* fmt, ... )
{
   va_list args;
   va_start( args, fmt );
   log( eLevel::Debug, fmt, args );
   va_end( args );
}

void Log::info( const char* fmt, ... )
{
   va_list args;
   va_start( args, fmt );
   log( eLevel::Info, fmt, args );
   va_end( args );
}

void Log::warning( const char* fmt, ... )
{
   va_list args;
   va_start( args, fmt );
   log( eLevel::Warn, fmt, args );
   va_end( args );
}

void Log::error( const char* fmt, ... )
{
   va_list args;
   va_start( args, fmt );
   log( eLevel::Error, fmt, args );
   va_end( args );
}

void Log::critical( const char* fmt, ... )
{
   va_list args;
   va_start( args, fmt );
   log( eLevel::Critical, fmt, args );
   va_end( args );
}

void Log::log( eLevel level, const char* fmt, ... )
{
   va_list args;
   va_start( args, fmt );
   log( level, fmt, args );
   va_end( args );
}

void Log::log( eLevel level, const char* fmt, va_list args )
{
   Event* event = Runtime::acquire_event( );
   if( event == nullptr )
      return;
   event->timestamp_ns( functions::now_ns( ) );
   event->thread_id( functions::tid( ) );
   event->phase( ePhase::Instant );
   event->level( level );
   event->message( fmt, args );

   Runtime::emit( event );
}
