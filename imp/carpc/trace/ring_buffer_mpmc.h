#pragma once

#include <atomic>

#include "ring_buffer_base.h"



namespace carpc::trace
{

   class RingBufferMPMC : public IRingBuffer
   {
         struct Cell
         {
            std::atomic< size_t >   sequence;
            const Event*            data;
         };

      public:
         explicit RingBufferMPMC( size_t capacity = CARPC_RING_BUFFER_SIZE );
         ~RingBufferMPMC( ) override;

         bool push( const Event* event ) override;
         const Event* pop( ) override;

      private:
         Cell*                   m_buffer;

         std::atomic< size_t >   m_head{ 0 };
         std::atomic< size_t >   m_tail{ 0 };
   };

} // namespace carpc::trace
