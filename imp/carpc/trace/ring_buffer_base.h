#pragma once

#include <cstddef>
#include <cstdio>

#include "carpc/trace/config.h"
#include "carpc/trace/event.h"



namespace carpc::trace
{

   class IRingBuffer
   {
         struct Count
         {
            size_t success{ 0 };
            size_t error{ 0 };
         };

      public:
         explicit IRingBuffer( size_t capacity = CARPC_RING_BUFFER_SIZE );
         virtual ~IRingBuffer( ) = default;

         virtual bool push( const Event* event ) = 0;
         virtual const Event* pop( ) = 0;

      protected:
         size_t                  m_capacity;

         Count                   m_push;
         Count                   m_pop;
   };

} // namespace carpc::trace
