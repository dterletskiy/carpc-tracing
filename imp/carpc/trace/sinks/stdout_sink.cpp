#include <unistd.h>
#include <cstdio>

#include "carpc/trace/sinks/stdout_sink.h"

using namespace carpc::trace;



void StdoutSink::emit_priv( const Event* event )
{
   char buffer[ CARPC_MESSAGE_LENGTH + 256 ];

   const int size = std::snprintf(
         buffer,
         sizeof( buffer ),
         "[%-*s] [%-*s] [%-*llu] [%*llu]   | %s\n",
         5, to_string( event->phase( ) ),
         8, to_string( event->level( ) ),
         16, static_cast< unsigned long long >( event->timestamp_ns( ) ),
         8, static_cast< unsigned long long >( event->thread_id( ) ),
         event->message( )
      );

   if( size > 0 )
   {
      ::write(
         STDOUT_FILENO,
         buffer,
         static_cast< size_t >( size )
      );
   }
}
