#include <unistd.h>
#include <vector>
#include <thread>

#include "carpc/trace/trace.h"



using namespace carpc::trace;



bool test_runtime( )
{
   StdoutSink sink;
   // BinaryFileSink sink( "trace.log" );
   Runtime::start( &sink );

   constexpr int num_threads = 10;
   constexpr int events_per_thread = 1;

   std::vector< std::thread > threads;
   CARPC_TRACE_LOG_TRACE( "! Thread started, pid=%d", getpid( ) );

   for( int t = 0; t < num_threads; ++t )
   {
      threads.emplace_back(
         [ t ]( )
         {
            CARPC_TRACE_LOG_TRACE( "Thread started" );

            {
               CARPC_TRACE_SCOPE( "main" );
               {
                  CARPC_TRACE_SCOPE( "work" );

                  for( int i = 0; i < events_per_thread; ++i )
                  // for( int i = 0; i > -1; ++i )
                  {
                     CARPC_TRACE_LOG_TRACE( "Thread %d - Event %d", t, i );
                     CARPC_TRACE_LOG_DEBUG( "Thread %d - Event %d", t, i );
                     CARPC_TRACE_LOG_INFO( "Thread %d - Event %d", t, i );
                     CARPC_TRACE_LOG_WARNING( "Thread %d - Event %d", t, i );
                     CARPC_TRACE_LOG_ERROR( "Thread %d - Event %d", t, i );
                     CARPC_TRACE_LOG_CRITICAL( "Thread %d - Event %d", t, i );

                     // std::this_thread::sleep_for( std::chrono::milliseconds( 1 ) );
                  }
               }
            }

            // std::this_thread::sleep_for( std::chrono::milliseconds( 1000 ) );

            CARPC_TRACE_LOG_TRACE( "Thread finished" );
         }
      );
   }

   for( auto& th : threads )
      th.join( );

   std::this_thread::sleep_for( std::chrono::milliseconds(50) );

   Runtime::stop( );

   return true;
}


int main( )
{
   test_runtime( );
   return 0;
}
