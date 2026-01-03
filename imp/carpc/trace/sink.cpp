#include "carpc/trace/runtime.h"
#include "carpc/trace/sink.h"



using namespace carpc::trace;



void ISink::emit( const Event* event )
{
   emit_priv( event );

   Runtime::release_event( event );
}