#pragma once

#include "carpc/trace/trace_event.h"



namespace carpc::trace
{

   class ITraceSink
   {
      public:
         ITraceSink( ) = default;
         virtual ~ITraceSink() = default;

         void emit( const TraceEvent* event );

      private:
         virtual void emit_priv( const TraceEvent* event ) = 0;
   };

} // namespace carpc::trace
