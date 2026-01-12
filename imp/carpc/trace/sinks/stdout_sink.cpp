#include <unistd.h>
#include <cstdio>

#include "carpc/trace/sinks/stdout_sink.h"
#include "carpc/trace/functions.h"

using namespace carpc::trace;



void StdoutSink::emit_priv( const Event* event )
{
   char buffer[ CARPC_MESSAGE_LENGTH + 256 ];

   const char* file_name =
      carpc::trace::utils::get_filename_ptr( event->file( ) );
   std::string file_line =
      std::string( file_name ) + ":" + std::to_string( event->line( ) );
   std::string function =
      carpc::trace::utils::get_namespace_class_func( event->function( ) );

   const int size = std::snprintf(
         buffer,
         sizeof( buffer ),
         "[%-*s] [%-*s] [%-*llu] [%*llu] [%-*s] [%-*s]   | %s\n",
         5, to_string( event->phase( ) ),
         8, to_string( event->level( ) ),
         16, static_cast< unsigned long long >( event->timestamp_ns( ) ),
         8, static_cast< unsigned long long >( event->thread_id( ) ),
         30, file_line.c_str( ),
         20, function.c_str( ),
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
