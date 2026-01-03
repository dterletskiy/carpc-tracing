#include "ring_buffer_base.h"



using namespace carpc::trace;



IRingBuffer::IRingBuffer( size_t capacity )
   : m_capacity( capacity )
{
}
