#pragma once



namespace carpc::trace
{

   class Scope
   {
      public:
         explicit Scope( const char* message );
         ~Scope( );

      private:
         const char* m_message;
   };

} // namespace carpc::trace
