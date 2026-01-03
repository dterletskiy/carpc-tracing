#include "carpc/trace/functions.h"
#include "carpc/trace/event.h"
#include "carpc/trace/runtime.h"
#include "carpc/trace/scope.h"



using namespace carpc::trace;



Scope::Scope( const char* message )
   : m_message( message )
{
   Event* event = Runtime::acquire_event( );
   if(event == nullptr)
      return;
   event->timestamp_ns( functions::now_ns( ) );
   event->thread_id( functions::tid( ) );
   event->phase( ePhase::Begin );
   event->message( m_message );

   Runtime::emit( event );
}

Scope::~Scope( )
{
   Event* event = Runtime::acquire_event( );
   if(event == nullptr)
      return;
   event->timestamp_ns( functions::now_ns( ) );
   event->thread_id( functions::tid( ) );
   event->phase( ePhase::End );
   event->message( m_message );

   Runtime::emit( event );
}
