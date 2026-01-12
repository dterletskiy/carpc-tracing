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
         void timestamp_ns( uint64_t value );

         uint64_t thread_id( ) const;
         void thread_id( uint64_t value );

         ePhase phase( ) const;
         void phase( ePhase value );

         eLevel level( ) const;
         void level( eLevel value );

         const char* message( ) const;
         void message( const char* fmt, ... );
         void message( const char* fmt, va_list args );

         const char* file( ) const;
         void file( const char* value );

         uint64_t line( ) const;
         void line( uint64_t value );

         const char* function( ) const;
         void function( const char* value );

      private:
         uint64_t    m_timestamp_ns{ 0 };
         uint64_t    m_thread_id{ 0 };
         ePhase      m_phase{ ePhase::Undefined };
         eLevel      m_level{ eLevel::Trace };
         char        m_message[ CARPC_MESSAGE_LENGTH ];
         const char* m_file{ nullptr };
         uint64_t    m_line{ 0 };
         const char* m_function{ nullptr };
   };

} // namespace carpc::trace
