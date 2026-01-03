#pragma once

#include <atomic>

#include "ring_buffer.h"



namespace carpc::trace
{

   struct ThreadContext
   {
      ThreadContext( );
      ~ThreadContext( );

      static ThreadContext& current( );

      RingBuffer           buffer;
      std::atomic< bool >  alive{ true };
   };

} // namespace carpc::trace
