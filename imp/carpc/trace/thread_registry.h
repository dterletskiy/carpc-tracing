#pragma once

#include <vector>
#include <mutex>



namespace carpc::trace
{

   class ThreadContext;

   class ThreadRegistry
   {
      public:
         using CONTEXTS = std::vector< ThreadContext* >;

      public:
         static ThreadContext* create_context( );
         static const CONTEXTS contexts( );

      private:
         static CONTEXTS      s_contexts;
         static std::mutex    s_mutex;
   };

} // namespace carpc::trace
