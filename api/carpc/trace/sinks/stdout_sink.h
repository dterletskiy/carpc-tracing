#pragma once

#include "carpc/trace/trace_sink.h"



namespace carpc::trace
{

   class StdoutSink final : public ITraceSink
   {
      public:
         StdoutSink( ) = default;
         ~StdoutSink( ) override = default;

      private:
         void emit_priv( const TraceEvent* event ) override;
   };

} // namespace carpc::trace
