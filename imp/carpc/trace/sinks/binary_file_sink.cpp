#include <unistd.h>
#include <fcntl.h>
#include <cstring>
#include <cstdio>

#include "carpc/trace/functions.h"
#include "carpc/trace/sinks/binary_file_sink.h"



using namespace carpc::trace;



static constexpr uint32_t TRACE_MAGIC = 0x43545243; // 'CRTC'
static constexpr uint16_t TRACE_VERSION = 1;

struct FileHeader
{
   uint32_t magic;        // TRACE_MAGIC
   uint16_t version;      // format version
   uint16_t header_size;  // sizeof(FileHeader)
   uint64_t start_time_ns;
};

static_assert( sizeof(FileHeader) == 16 );



enum class RecordType : uint8_t
{
   Event = 1
};

struct EventRecord
{
   uint8_t   type;          // RecordType::Event
   uint8_t   phase;         // TracePhase
   uint8_t   level;         // TraceLevel
   uint8_t   reserved;

   uint64_t  thread_id;
   uint64_t  timestamp_ns;

   uint16_t  message_len;
   // char name[ message_len ]; // immediately after
};



BinaryFileSink::BinaryFileSink( const char* path )
{
   m_fd = ::open( path, O_CREAT | O_TRUNC | O_WRONLY, 0644 );

   m_start_time_ns = carpc::trace::utils::now_ns( );

   FileHeader header
   {
      TRACE_MAGIC,
      TRACE_VERSION,
      sizeof( FileHeader ),
      m_start_time_ns
   };

   ::write( m_fd, &header, sizeof(header) );
}

BinaryFileSink::~BinaryFileSink( )
{
   ::close( m_fd );
}

void BinaryFileSink::emit_priv( const Event* event )
{
   const uint16_t message_len =
      static_cast< uint16_t >( std::strlen( event->message( ) ) );

   EventRecord rec
   {
      static_cast< uint8_t >( RecordType::Event ),
      static_cast< uint8_t >( event->phase( ) ),
      static_cast< uint8_t >( event->level( ) ),
      0,
      event->thread_id( ),
      event->timestamp_ns( ),
      message_len
   };

   ::write( m_fd, &rec, sizeof(rec) );
   ::write( m_fd, event->message( ), message_len );
}
