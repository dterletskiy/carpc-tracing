#pragma once

#include <atomic>

#include "ring_buffer_base.h"



namespace carpc::trace
{

   class RingBufferSPSC : public IRingBuffer
   {
      public:
         explicit RingBufferSPSC( size_t capacity = CARPC_RING_BUFFER_SIZE );
         ~RingBufferSPSC( ) override;

         bool push( const Event* event ) override;
         const Event* pop( ) override;

      private:
         const Event**           m_buffer;

         std::atomic< size_t >   m_head{ 0 };
         std::atomic< size_t >   m_tail{ 0 };
   };

} // namespace carpc::trace
