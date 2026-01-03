#pragma once

#include <mutex>
#include <cstddef>
#include <cstdio>

#include "carpc/trace/config.h"
#include "carpc/trace/event.h"



namespace carpc::trace
{

   class RingBufferMutex
   {
         struct Count
         {
            size_t success{ 0 };
            size_t error{ 0 };
         };

      public:
         explicit RingBufferMutex( size_t capacity = CARPC_RING_BUFFER_SIZE );
         ~RingBufferMutex( );

         bool push( const Event* event );
         const Event* pop( );

      private:
         size_t                  m_capacity;
         const Event**           m_buffer;

         size_t                  m_head{ 0 };
         size_t                  m_tail{ 0 };
         std::mutex              m_mutex;

         Count                   m_push;
         Count                   m_pop;
   };

} // namespace carpc::trace
