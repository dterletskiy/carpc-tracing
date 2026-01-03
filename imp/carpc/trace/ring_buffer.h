#pragma once

#include <atomic>
#include <cstddef>
#include <cstdio>

#include "ring_buffer_spsc.h"
#include "ring_buffer_mpmc.h"
#include "ring_buffer_mutex.h"



namespace carpc::trace
{

   using RingBuffer = RingBufferSPSC;
   // using RingBuffer = RingBufferMPMC;
   // using RingBuffer = RingBufferMutex;

} // namespace carpc::trace
