#pragma once

#include <cstddef>
#include <atomic>

#include "carpc/trace/config.h"
#include "carpc/trace/event.h"



namespace carpc::trace
{

   class EventPool
   {
      public:
         EventPool( size_t capacity = CARPC_EVENT_POOL_SIZE );
         ~EventPool( );

         Event* acquire( );
         void release( const Event* event );

      private:
         size_t      m_capacity;
         Event* mp_storage;
         // bool*       mp_used;
         // size_t      m_head{ 0 };
         std::atomic< size_t > m_head { 0 };
         std::atomic< bool >* mp_used;
   };

} // namespace carpc::trace
