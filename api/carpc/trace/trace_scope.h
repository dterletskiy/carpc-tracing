#pragma once



namespace carpc::trace
{

   class TraceScope
   {
      public:
         explicit TraceScope( const char* message );
         ~TraceScope( );

      private:
         const char* m_message;
   };

} // namespace carpc::trace
