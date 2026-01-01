#include "carpc/trace/trace_level.h"



namespace carpc::trace
{

   const char* to_string( eTraceLevel level )
   {
      switch( level )
      {
         case eTraceLevel::Trace:
            return "Trace";
         case eTraceLevel::Debug:
            return "Debug";
         case eTraceLevel::Info:
            return "Info";
         case eTraceLevel::Warn:
            return "Warn";
         case eTraceLevel::Error:
            return "Error";
         case eTraceLevel::Critical:
            return "Critical";
         default:
            return "UNKN";
      }
   }

} // namespace carpc::trace
