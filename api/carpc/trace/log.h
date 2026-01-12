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

         static void log(
               eLevel level,
               const char* file, uint64_t line, const char* function,
               const char* fmt, ...
            );
         static void log(
               eLevel level,
               const char* file, uint64_t line, const char* function,
               const char* fmt, va_list args
            );
   };

} // namespace carpc::trace
