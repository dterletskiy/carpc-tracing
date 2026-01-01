#include <cstdio>

#include "carpc/trace/trace_event.h"



using namespace carpc::trace;



uint64_t TraceEvent::timestamp_ns( ) const
{
   return m_timestamp_ns;
}

void TraceEvent::timestamp_ns( uint64_t val )
{
   m_timestamp_ns = val;
}

uint64_t TraceEvent::thread_id( ) const
{
   return m_thread_id;
}

void TraceEvent::thread_id( uint64_t val )
{
   m_thread_id = val;
}

eTracePhase TraceEvent::phase( ) const
{
   return m_phase;
}

void TraceEvent::phase( eTracePhase val )
{
   m_phase = val;
}

eTraceLevel TraceEvent::level( ) const
{
   return m_level;
}

void TraceEvent::level( eTraceLevel val )
{
   m_level = val;
}

const char* TraceEvent::message( ) const
{
   return m_message;
}

void TraceEvent::message( const char* fmt, ... )
{
   va_list args;
   va_start( args, fmt );
   const int size = std::vsnprintf( m_message, sizeof(m_message), fmt, args );
   va_end( args );
}

void TraceEvent::message( const char* fmt, va_list args )
{
   const int size = std::vsnprintf( m_message, sizeof(m_message), fmt, args );
}
