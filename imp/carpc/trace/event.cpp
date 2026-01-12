#include <cstdio>

#include "carpc/trace/event.h"



namespace carpc::trace {

   const char* to_string( eLevel level )
   {
      switch( level )
      {
         case eLevel::Trace:
            return "Trace";
         case eLevel::Debug:
            return "Debug";
         case eLevel::Info:
            return "Info";
         case eLevel::Warn:
            return "Warn";
         case eLevel::Error:
            return "Error";
         case eLevel::Critical:
            return "Critical";
         default:
            return "UNKN";
      }
   }

   const char* to_string( ePhase phase )
   {
      switch( phase )
      {
         case ePhase::Begin:
            return "BEGIN";
         case ePhase::End:
            return "END";
         case ePhase::Instant:
            return "INST";
         default:
            return "UNKN";
      }
   }

}

using namespace carpc::trace;



uint64_t Event::timestamp_ns( ) const
{
   return m_timestamp_ns;
}

void Event::timestamp_ns( uint64_t value )
{
   m_timestamp_ns = value;
}

uint64_t Event::thread_id( ) const
{
   return m_thread_id;
}

void Event::thread_id( uint64_t value )
{
   m_thread_id = value;
}

ePhase Event::phase( ) const
{
   return m_phase;
}

void Event::phase( ePhase value )
{
   m_phase = value;
}

eLevel Event::level( ) const
{
   return m_level;
}

void Event::level( eLevel value )
{
   m_level = value;
}

const char* Event::message( ) const
{
   return m_message;
}

void Event::message( const char* fmt, ... )
{
   va_list args;
   va_start( args, fmt );
   const int size = std::vsnprintf( m_message, sizeof(m_message), fmt, args );
   va_end( args );
}

void Event::message( const char* fmt, va_list args )
{
   const int size = std::vsnprintf( m_message, sizeof(m_message), fmt, args );
}

const char* Event::file( ) const
{
   return m_file;
}

void Event::file( const char* value )
{
   m_file = value;
}

uint64_t Event::line( ) const
{
   return m_line;
}

void Event::line( uint64_t value )
{
   m_line = value;
}

const char* Event::function( ) const
{
   return m_function;
}

void Event::function( const char* value )
{
   m_function = value;
}
