#pragma once

#include <atomic>
#include <cstddef>
#include <cstdio>

#include "carpc/trace/trace_ring_buffer_spsc.h"
#include "carpc/trace/trace_ring_buffer_mpmc.h"
#include "carpc/trace/trace_ring_buffer_mutex.h"



namespace carpc::trace
{

   using TraceRingBuffer = TraceRingBufferSPSC;
   // using TraceRingBuffer = TraceRingBufferMPMC;
   // using TraceRingBuffer = TraceRingBufferMutex;

} // namespace carpc::trace
