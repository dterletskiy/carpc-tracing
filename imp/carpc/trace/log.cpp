#include "carpc/trace/functions.h"
#include "carpc/trace/event.h"
#include "carpc/trace/runtime.h"
#include "carpc/trace/log.h"



using namespace carpc::trace;



void Log::log(
      eLevel level,
      const char* file,
      uint64_t line,
      const char* function,
      const char* fmt,
      ...
   )
{
   va_list args;
   va_start( args, fmt );
   log( level, file, line, function, fmt, args );
   va_end( args );
}

void Log::log(
      eLevel level,
      const char* file,
      uint64_t line,
      const char* function,
      const char* fmt,
      va_list args
   )
{
   Event* event = Runtime::acquire_event( );
   if( event == nullptr )
      return;
   event->timestamp_ns( carpc::trace::utils::now_ns( ) );
   event->thread_id( carpc::trace::utils::tid( ) );
   event->phase( ePhase::Instant );
   event->level( level );
   event->message( fmt, args );
   event->file( file );
   event->line( line );
   event->function( function );

   Runtime::emit( event );
}
