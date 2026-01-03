#pragma once

#include <mutex>

#include "ring_buffer_base.h"



namespace carpc::trace
{

   class RingBufferMutex : public IRingBuffer
   {
      public:
         explicit RingBufferMutex( size_t capacity = CARPC_RING_BUFFER_SIZE );
         ~RingBufferMutex( ) override;

         bool push( const Event* event ) override;
         const Event* pop( ) override;

      private:
         const Event**           m_buffer;

         size_t                  m_head{ 0 };
         size_t                  m_tail{ 0 };
         std::mutex              m_mutex;
   };

} // namespace carpc::trace
