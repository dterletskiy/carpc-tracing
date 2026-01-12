#pragma once

#include "carpc/trace/config.h"
#include "carpc/trace/scope.h"
#include "carpc/trace/log.h"



#if CARPC_TRACE_ENABLE

   #define CARPC_TRACE_SCOPE( msg ) \
      carpc::trace::Scope _carpc_trace_scope_##__LINE__( msg )

   #define CARPC_TRACE_LOG_TRACE( fmt, ... )    \
      carpc::trace::Log::log(                   \
            carpc::trace::eLevel::Trace,        \
            __FILE__, __LINE__, __FUNCTION__,   \
            fmt, ##__VA_ARGS__                  \
         )

   #define CARPC_TRACE_LOG_DEBUG( fmt, ... )    \
      carpc::trace::Log::log(                   \
            carpc::trace::eLevel::Debug,        \
            __FILE__, __LINE__, __FUNCTION__,   \
            fmt, ##__VA_ARGS__                  \
         )

   #define CARPC_TRACE_LOG_INFO( fmt, ... )     \
      carpc::trace::Log::log(                   \
            carpc::trace::eLevel::Info,         \
            __FILE__, __LINE__, __FUNCTION__,   \
            fmt, ##__VA_ARGS__                  \
         )

   #define CARPC_TRACE_LOG_WARNING( fmt, ... )  \
      carpc::trace::Log::log(                   \
            carpc::trace::eLevel::Warn,         \
            __FILE__, __LINE__, __FUNCTION__,   \
            fmt, ##__VA_ARGS__                  \
         )

   #define CARPC_TRACE_LOG_ERROR( fmt, ... )    \
      carpc::trace::Log::log(                   \
            carpc::trace::eLevel::Error,        \
            __FILE__, __LINE__, __FUNCTION__,   \
            fmt, ##__VA_ARGS__                  \
         )

   #define CARPC_TRACE_LOG_CRITICAL( fmt, ... ) \
      carpc::trace::Log::log(                   \
            carpc::trace::eLevel::Critical,     \
            __FILE__, __LINE__, __FUNCTION__,   \
            fmt, ##__VA_ARGS__                  \
         )

#else

   #define CARPC_TRACE_SCOPE( fmt )
   #define CARPC_TRACE_LOG_TRACE( fmt )

#endif
