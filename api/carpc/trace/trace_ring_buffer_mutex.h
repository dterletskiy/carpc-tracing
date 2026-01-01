#pragma once

#include <mutex>
#include <cstddef>
#include <cstdio>

#include "carpc/trace/trace_config.h"
#include "carpc/trace/trace_event.h"



namespace carpc::trace
{

   class TraceRingBufferMutex
   {
         struct Count
         {
            size_t success{ 0 };
            size_t error{ 0 };
         };

      public:
         explicit TraceRingBufferMutex( size_t capacity = CARPC_RING_BUFFER_SIZE );
         ~TraceRingBufferMutex( );

         bool push( const TraceEvent* event );
         const TraceEvent* pop( );

      private:
         size_t                  m_capacity;
         const TraceEvent**      m_buffer;

         size_t                  m_head{ 0 };
         size_t                  m_tail{ 0 };
         std::mutex              m_mutex;

         Count                   m_push;
         Count                   m_pop;
   };

} // namespace carpc::trace
