#pragma once

#include "carpc/trace/sink.h"



namespace carpc::trace
{

   class StdoutSink final : public ISink
   {
      public:
         StdoutSink( ) = default;
         ~StdoutSink( ) override = default;

      private:
         void emit_priv( const Event* event ) override;
   };

} // namespace carpc::trace
