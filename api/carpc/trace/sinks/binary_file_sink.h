#pragma once

#include "carpc/trace/sink.h"



namespace carpc::trace
{

   class BinaryFileSink final : public ISink
   {
      public:
         BinaryFileSink( const char* path );
         ~BinaryFileSink( ) override;

      private:
         void emit_priv( const Event* event ) override;

      private:
         int         m_fd;
         uint64_t    m_start_time_ns;
   };

} // namespace carpc::trace
