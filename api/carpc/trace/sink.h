#pragma once

#include "carpc/trace/event.h"



namespace carpc::trace
{

   class ISink
   {
      public:
         ISink( ) = default;
         virtual ~ISink() = default;

         void emit( const Event* event );

      private:
         virtual void emit_priv( const Event* event ) = 0;
   };

} // namespace carpc::trace
