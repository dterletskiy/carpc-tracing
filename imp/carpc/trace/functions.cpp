#include "carpc/trace/functions.h"



#include <cstring>

namespace carpc::trace::utils {

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

namespace carpc::trace::utils {

   uint32_t pid( )
   {
      return static_cast< uint32_t >( getpid( ) );
   }

   uint32_t tid( )
   {
      static thread_local uint32_t t
         = static_cast< uint32_t >( syscall( SYS_gettid ) );
      return t;
   }

}



#include <time.h>

namespace carpc::trace::utils {

   uint64_t now_ns( )
   {
      timespec ts;
      clock_gettime( CLOCK_MONOTONIC_RAW, &ts );

      return static_cast< uint64_t >( ts.tv_sec ) * 1000000000ULL +
             static_cast< uint64_t >( ts.tv_nsec );
   }

}



#include <cstring>
#include <string>

namespace carpc::trace::utils {


   const char* get_filename_ptr( const char* path )
   {
      const char* last = path;

      for( const char *p = path; *p != '\0'; ++p )
      {
         if(*p == '/')
         {
            last = p + 1;
         }
      }

      return last;
   }

   std::string get_namespace_class_func( const char* pretty_func )
   {
      std::string s( pretty_func );

      // 1. Remove function arguments along with any spaces before '('
      auto pos = s.find('(');
      if( pos != std::string::npos )
      {
         // Move left to remove all spaces immediately before '('
         while( pos > 0 && s[pos - 1] == ' ' )
            --pos;

         // Resize the string to remove the argument list and trailing spaces
         s.resize( pos );
      }

      // 2. Remove the return type, leaving only namespace/class/function name
      //    We find the last space, which separates the return type 
      //    from the function name
      auto space_pos = s.rfind(' ');
      if( std::string::npos != space_pos )
      {
         // erase everything before and including the last space
         s.erase( 0, space_pos + 1 ); 
      }

      // The resulting string now contains only 'namespace::class::function'
      return s;
   }
}
