#pragma once

#include <cstdint>



namespace carpc::trace
{

   enum class eTraceLevel : uint8_t
   {
      Trace = 0,
      Debug,
      Info,
      Warn,
      Error,
      Critical
   };

   const char* to_string( eTraceLevel level );


} // namespace carpc::trace
