#pragma once

#include <cstdint>
#include <cstdarg>

#include "carpc/trace/trace_config.h"
#include "carpc/trace/trace_phase.h"
#include "carpc/trace/trace_level.h"



namespace carpc::trace
{

   struct TraceEvent
   {
      public:
         TraceEvent( ) = default;
         ~TraceEvent( ) = default;

         uint64_t timestamp_ns( ) const;
         void timestamp_ns( uint64_t val );

         uint64_t thread_id( ) const;
         void thread_id( uint64_t val );

         eTracePhase phase( ) const;
         void phase( eTracePhase val );

         eTraceLevel level( ) const;
         void level( eTraceLevel val );

         const char* message( ) const;
         void message( const char* fmt, ... );
         void message( const char* fmt, va_list args );

      private:
         uint64_t    m_timestamp_ns{ 0 };
         uint32_t    m_thread_id{ 0 };
         eTracePhase m_phase{ eTracePhase::Undefined };
         eTraceLevel m_level{ eTraceLevel::Trace };
         char        m_message[ CARPC_MESSAGE_LENGTH ];
   };

} // namespace carpc::trace
