#pragma once

#include <atomic>



namespace carpc::trace::os
{

   class Futex
   {
      public:
         void wait( );
         void wake( );
         void reset( );

      private:
         std::atomic< int > m_val{ 0 };
   };

} // namespace carpc::trace::os
