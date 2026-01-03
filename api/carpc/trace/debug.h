#pragma once

#include <cstdio>
#include <cstring>
#include <string>
#include <unistd.h>
#include <sys/syscall.h>



#ifdef CARPC_TRACE_DEBUG_ENABLE_LOCAL
   #define CARPC_TRACE_DEBUG_ENABLE CARPC_TRACE_DEBUG_ENABLE_LOCAL
#else
   #define CARPC_TRACE_DEBUG_ENABLE 0
#endif

#if CARPC_TRACE_DEBUG_ENABLE

   #define __N_TID__    8
   #define __N_FILE__   30
   #define __N_FUNC__   50



   #define __PID__                                       \
      ( static_cast< pid_t >( getpid( ) ) )

   #define __TID__                                       \
      ( static_cast< pid_t >( syscall( SYS_gettid ) ) )

   #define __FILENAME__                                  \
      ( strrchr( __FILE__, '/' )                         \
         ? strrchr( __FILE__, '/' ) + 1                  \
         : __FILE__ )

   inline std::string get_namespace_class_func( const char* pretty_func )
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

   #define __NS_FUNCTION__                               \
      get_namespace_class_func(                          \
         __PRETTY_FUNCTION__ ).c_str( )



   #define __CARPC_FUNCTION__ __NS_FUNCTION__
   #define __CARPC_LINE__     __LINE__
   #define __CARPC_FILE__     __FILENAME__

   #define CARPC_TRACE_DEBUG( format, ... )              \
      do                                                 \
      {                                                  \
         char __prefix_tid[ __N_TID__ + 1 ];             \
         snprintf(                                       \
               __prefix_tid, sizeof(__prefix_tid),       \
               "%d",                                     \
               __TID__                                   \
            );                                           \
                                                         \
         char __prefix_file[ __N_FILE__ + 1 ];           \
         snprintf(                                       \
               __prefix_file, sizeof(__prefix_file),     \
               "%s:%d",                                  \
               __CARPC_FILE__, __CARPC_LINE__            \
            );                                           \
                                                         \
         char __prefix_func[ __N_FUNC__ + 1 ];           \
         snprintf(                                       \
               __prefix_func, sizeof(__prefix_func),     \
               "%s",                                     \
               __CARPC_FUNCTION__                        \
            );                                           \
                                                         \
         printf(                                         \
               "[%*s]" "   "                             \
               "[%-*s]" "   "                            \
               "[%-*s]" "   | "                          \
               format "\n",                              \
               __N_TID__, __prefix_tid,                  \
               __N_FILE__, __prefix_file,                \
               __N_FUNC__, __prefix_func,                \
               ##__VA_ARGS__                             \
            );                                           \
      } while( 0 )

#else

   #define CARPC_TRACE_DEBUG( format, ... )

#endif
