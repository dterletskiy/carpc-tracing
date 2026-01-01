#pragma once

#include "carpc/trace/trace_config.h"
#include "carpc/trace/trace_scope.h"
#include "carpc/trace/trace_log.h"



#if CARPC_TRACE_ENABLE

   #define CARPC_TRACE_SCOPE( name ) \
      carpc::trace::TraceScope _carpc_trace_scope_##__LINE__( name )

   #define CARPC_TRACE_LOG_TRACE( name, ... ) \
      carpc::trace::TraceLog::trace( name, ##__VA_ARGS__ )

   #define CARPC_TRACE_LOG_DEBUG( name, ... ) \
      carpc::trace::TraceLog::debug( name, ##__VA_ARGS__ )

   #define CARPC_TRACE_LOG_INFO( name, ... ) \
      carpc::trace::TraceLog::info( name, ##__VA_ARGS__ )

   #define CARPC_TRACE_LOG_WARNING( name, ... ) \
      carpc::trace::TraceLog::warning( name, ##__VA_ARGS__ )

   #define CARPC_TRACE_LOG_ERROR( name, ... ) \
      carpc::trace::TraceLog::error( name, ##__VA_ARGS__ )

   #define CARPC_TRACE_LOG_CRITICAL( name, ... ) \
      carpc::trace::TraceLog::critical( name, ##__VA_ARGS__ )

#else

   #define CARPC_TRACE_SCOPE( name )
   #define CARPC_TRACE_LOG_TRACE( name )

#endif
