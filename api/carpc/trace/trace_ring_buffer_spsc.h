#pragma once

#include <atomic>
#include <cstddef>
#include <cstdio>

#include "carpc/trace/trace_config.h"
#include "carpc/trace/trace_event.h"



namespace carpc::trace
{

   class TraceRingBufferSPSC
   {
         struct Count
         {
            size_t success{ 0 };
            size_t error{ 0 };
         };

      public:
         explicit TraceRingBufferSPSC( size_t capacity = CARPC_RING_BUFFER_SIZE );
         ~TraceRingBufferSPSC( );

         bool push( const TraceEvent* event );
         const TraceEvent* pop( );

      private:
         size_t                  m_capacity;
         const TraceEvent**      m_buffer;

         std::atomic< size_t >   m_head{ 0 };
         std::atomic< size_t >   m_tail{ 0 };

         Count                   m_push{ 0 };
         Count                   m_pop{ 0 };
   };

} // namespace carpc::trace
