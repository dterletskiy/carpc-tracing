#pragma once

#include <cstdarg>

#include "carpc/trace/event.h"



namespace carpc::trace
{

   class Log
   {
      public:
         Log( ) = default;
         ~Log( ) = default;

         static void trace( const char* fmt, ... );
         static void debug( const char* fmt, ... );
         static void info( const char* fmt, ... );
         static void warning( const char* fmt, ... );
         static void error( const char* fmt, ... );
         static void critical( const char* fmt, ... );

         static void log( eLevel level, const char* fmt, ... );
         static void log( eLevel level, const char* fmt, va_list args );
   };

} // namespace carpc::trace
