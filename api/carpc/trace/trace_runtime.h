#pragma once

#include "carpc/trace/trace_level.h"



namespace carpc::trace {

   class ITraceSink;
   class TraceEvent;

} // namespace carpc::trace

namespace carpc::trace::runtime {

   static void start( ITraceSink* sink );
   static void stop( );

   static void emit( const TraceEvent* event );

   static TraceEvent* acquire_event( );
   static void release_event( const TraceEvent* event );

   static void consumer_loop( );
   static void consumer_loop_sort( );

} // namespace carpc::trace::runtime

namespace carpc::trace
{

   class TraceRuntime
   {
      public:
         static void start( ITraceSink* sink );
         static void stop( );

         static void emit( const TraceEvent* event );

      public:
         static TraceEvent* acquire_event( );
         static void release_event( const TraceEvent* event );

      public:
         static void min_level( eTraceLevel level );
         static eTraceLevel min_level( );

      private:
         static void consumer_loop( );
         static void consumer_loop_sort( );
   };

} // namespace carpc::trace
