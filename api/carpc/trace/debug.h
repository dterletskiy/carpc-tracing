#pragma once

#include <cstdio>

#include "carpc/trace/functions.h"



#ifdef CARPC_TRACE_DEBUG_ENABLE_LOCAL
   #define CARPC_TRACE_DEBUG_ENABLE CARPC_TRACE_DEBUG_ENABLE_LOCAL
#else
   #define CARPC_TRACE_DEBUG_ENABLE 0
#endif

#if CARPC_TRACE_DEBUG_ENABLE

   #define __N_TID__    8
   #define __N_FILE__   30
   #define __N_FUNC__   50



   #define __CARPC_PID__ carpc::trace::utils::pid( )

   #define __CARPC_TID__ carpc::trace::utils::tid( )

   #define __CARPC_FUNCTION__                            \
      carpc::trace::utils::get_namespace_class_func(     \
         __PRETTY_FUNCTION__ ).c_str( )

   #define __CARPC_LINE__ __LINE__

   #define __CARPC_FILE__     \
      carpc::trace::utils::get_filename_ptr( __FILE__ )

   #define __CARPC_TRACE_DEBUG__(                        \
         N_TID, PREFIX_TID,                              \
         N_FILE, PREFIX_FILE,                            \
         N_FUNC, PREFIX_FUNC,                            \
         format, ...                                     \
      )                                                  \
         printf(                                         \
               "[%*d]" "   "                             \
               "[%-*s]" "   "                            \
               "[%-*s]" "   | "                          \
               format "\n",                              \
               N_TID, PREFIX_TID,                        \
               N_FILE, PREFIX_FILE,                      \
               N_FUNC, PREFIX_FUNC,                      \
               ##__VA_ARGS__                             \
            );


   #define CARPC_TRACE_DEBUG( format, ... )              \
      do                                                 \
      {                                                  \
         char __prefix_file[ __N_FILE__ + 1 ];           \
         snprintf(                                       \
               __prefix_file, sizeof(__prefix_file),     \
               "%s:%d",                                  \
               __CARPC_FILE__, __CARPC_LINE__            \
            );                                           \
                                                         \
         __CARPC_TRACE_DEBUG__(                          \
               __N_TID__, __CARPC_TID__,                 \
               __N_FILE__, __prefix_file,                \
               __N_FUNC__, __CARPC_FUNCTION__,           \
               format, ##__VA_ARGS__                     \
            );                                           \
      } while( 0 )

#else

   #define CARPC_TRACE_DEBUG( format, ... )

#endif
