#pragma once

#include <cstdint>
#include <cstdarg>

#include "carpc/trace/config.h"



namespace carpc::trace
{

   enum class eLevel : uint8_t
   {
      Trace = 0,
      Debug,
      Info,
      Warn,
      Error,
      Critical
   };
   const char* to_string( eLevel level );

   enum class ePhase : uint8_t
   {
      Begin,
      End,
      Instant,
      Undefined
   };
   const char* to_string( ePhase phase );

   struct Event
   {
      public:
         Event( ) = default;
         ~Event( ) = default;

         uint64_t timestamp_ns( ) const;
         void timestamp_ns( uint64_t val );

         uint64_t thread_id( ) const;
         void thread_id( uint64_t val );

         ePhase phase( ) const;
         void phase( ePhase val );

         eLevel level( ) const;
         void level( eLevel val );

         const char* message( ) const;
         void message( const char* fmt, ... );
         void message( const char* fmt, va_list args );

      private:
         uint64_t    m_timestamp_ns{ 0 };
         uint32_t    m_thread_id{ 0 };
         ePhase      m_phase{ ePhase::Undefined };
         eLevel      m_level{ eLevel::Trace };
         char        m_message[ CARPC_MESSAGE_LENGTH ];
   };

} // namespace carpc::trace
