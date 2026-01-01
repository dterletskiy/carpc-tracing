#include "carpc/trace/functions.h"



#include <cstring>

namespace carpc::functions {

   size_t strcpy( char *dst, size_t dst_size, const char *src )
   {
      size_t src_len;

      if( 0 == dst_size )
      {
         return strlen( src );
      }

      src_len = strlen( src );

      if( src_len >= dst_size )
      {
         memcpy( dst, src, dst_size - 1 );
         dst[ dst_size - 1 ] = '\0';
      }
      else
      {
         memcpy( dst, src, src_len + 1 );
      }

      return src_len;
   }

}



#include <unistd.h>
#include <sys/syscall.h>

namespace carpc::functions {

   uint32_t tid( )
   {
      return static_cast< uint32_t >( syscall( SYS_gettid ) );
   }

}



#include <time.h>

namespace carpc::functions {

   uint64_t now_ns( )
   {
      timespec ts;
      clock_gettime( CLOCK_MONOTONIC_RAW, &ts );

      return static_cast< uint64_t >( ts.tv_sec ) * 1000000000ULL +
             static_cast< uint64_t >( ts.tv_nsec );
   }

}
