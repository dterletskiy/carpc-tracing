#pragma once

#include <atomic>
#include <cstddef>
#include <cstdio>

#include "carpc/trace/config.h"
#include "carpc/trace/event.h"



namespace carpc::trace
{

   class RingBufferMPMC
   {
         struct Count
         {
            size_t success{ 0 };
            size_t error{ 0 };
         };

         struct Cell
         {
            std::atomic< size_t >   sequence;
            const Event*            data;
         };

      public:
         explicit RingBufferMPMC( size_t capacity = CARPC_RING_BUFFER_SIZE );
         ~RingBufferMPMC( );

         bool push( const Event* event );
         const Event* pop( );

      private:
         size_t                  m_capacity;
         Cell*                   m_buffer;

         std::atomic< size_t >   m_head{ 0 };
         std::atomic< size_t >   m_tail{ 0 };

         Count                   m_push{ 0 };
         Count                   m_pop{ 0 };

   };

} // namespace carpc::trace
