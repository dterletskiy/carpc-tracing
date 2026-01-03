#pragma once

#include "carpc/trace/config.h"
#include "carpc/trace/scope.h"
#include "carpc/trace/log.h"



#if CARPC_TRACE_ENABLE

   #define CARPC_TRACE_SCOPE( name ) \
      carpc::trace::Scope _carpc_trace_scope_##__LINE__( name )

   #define CARPC_TRACE_LOG_TRACE( name, ... ) \
      carpc::trace::Log::trace( name, ##__VA_ARGS__ )

   #define CARPC_TRACE_LOG_DEBUG( name, ... ) \
      carpc::trace::Log::debug( name, ##__VA_ARGS__ )

   #define CARPC_TRACE_LOG_INFO( name, ... ) \
      carpc::trace::Log::info( name, ##__VA_ARGS__ )

   #define CARPC_TRACE_LOG_WARNING( name, ... ) \
      carpc::trace::Log::warning( name, ##__VA_ARGS__ )

   #define CARPC_TRACE_LOG_ERROR( name, ... ) \
      carpc::trace::Log::error( name, ##__VA_ARGS__ )

   #define CARPC_TRACE_LOG_CRITICAL( name, ... ) \
      carpc::trace::Log::critical( name, ##__VA_ARGS__ )

#else

   #define CARPC_TRACE_SCOPE( name )
   #define CARPC_TRACE_LOG_TRACE( name )

#endif
