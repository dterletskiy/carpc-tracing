#pragma once

#include <cstdint>



namespace carpc::trace
{

   enum class eTracePhase : uint8_t
   {
      Begin,
      End,
      Instant,
      Undefined
   };

   const char* to_string( eTracePhase phase );


} // namespace carpc::trace
