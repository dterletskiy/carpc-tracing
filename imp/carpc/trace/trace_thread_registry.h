#pragma once

#include <vector>
#include <mutex>



namespace carpc::trace
{

   class TraceThreadContext;

   class TraceThreadRegistry
   {
      public:
         using CONTEXTS = std::vector< TraceThreadContext* >;

      public:
         static TraceThreadContext* create_context( );
         static const CONTEXTS contexts( );

      private:
         static CONTEXTS      s_contexts;
         static std::mutex    s_mutex;
   };

} // namespace carpc::trace
