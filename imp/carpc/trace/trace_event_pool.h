#pragma once

#include <cstddef>
#include <atomic>

#include "carpc/trace/trace_config.h"
#include "carpc/trace/trace_event.h"



namespace carpc::trace
{

   class TraceEventPool
   {
      public:
         TraceEventPool( size_t capacity = CARPC_EVENT_POOL_SIZE );
         ~TraceEventPool( );

         TraceEvent* acquire( );
         void release( const TraceEvent* event );

      private:
         size_t      m_capacity;
         TraceEvent* mp_storage;
         // bool*       mp_used;
         // size_t      m_head{ 0 };
         std::atomic< size_t > m_head { 0 };
         std::atomic< bool >* mp_used;
   };

} // namespace carpc::trace
