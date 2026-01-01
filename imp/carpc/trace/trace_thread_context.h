#pragma once

#include <atomic>

#include "carpc/trace/trace_ring_buffer.h"



namespace carpc::trace
{

   struct TraceThreadContext
   {
      TraceThreadContext( );
      ~TraceThreadContext( );

      static TraceThreadContext& current( );

      TraceRingBuffer      buffer;
      std::atomic< bool >  alive{ true };
   };

} // namespace carpc::trace
