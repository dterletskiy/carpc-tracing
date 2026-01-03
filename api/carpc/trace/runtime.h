#pragma once

#include "carpc/trace/event.h"



namespace carpc::trace {

   class ISink;

} // namespace carpc::trace

namespace carpc::trace
{

   class Runtime
   {
      public:
         static void start( ISink* sink );
         static void stop( );

         static void emit( const Event* event );

      public:
         static Event* acquire_event( );
         static void release_event( const Event* event );

      public:
         static void min_level( eLevel level );
         static eLevel min_level( );

      private:
         static void consumer_loop( );
         static void consumer_loop_sort( );
   };

} // namespace carpc::trace
