#include "carpc/trace/trace_phase.h"



namespace carpc::trace
{

   const char* to_string( eTracePhase phase )
   {
      switch( phase )
      {
         case eTracePhase::Begin:
            return "BEGIN";
         case eTracePhase::End:
            return "END";
         case eTracePhase::Instant:
            return "INST";
         default:
            return "UNKN";
      }
   }

} // namespace carpc::trace
