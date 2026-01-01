#include <linux/futex.h>
#include <sys/syscall.h>
#include <unistd.h>

#include "carpc/trace/futex.h"



using namespace carpc::trace::os;



void Futex::wait( )
{
   int v = 0;
   syscall( SYS_futex, &m_val, FUTEX_WAIT, v, nullptr, nullptr, 0 );
}

void Futex::wake( )
{
   m_val.store( 1, std::memory_order_release );
   syscall( SYS_futex, &m_val, FUTEX_WAKE, 1, nullptr, nullptr, 0 );
}

void Futex::reset( )
{
   m_val.store( 0, std::memory_order_release );
}
