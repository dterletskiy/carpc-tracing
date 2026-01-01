#include <cstddef>
#include <cstdint>



namespace carpc::functions {

   /**
    * @brief Safely copies a C-string into a destination buffer with truncation.
    *
    * Copies the null-terminated string from src to dst, ensuring no 
    * buffer overflow.
    * If src is longer than dst_size, it is truncated and dst is always 
    * null-terminated.
    *
    * @param dst Pointer to the destination buffer.
    * @param dst_size Size of the destination buffer in bytes.
    * @param src Pointer to the null-terminated source string.
    * @return The length of src (excluding null terminator). 
    *    If >= dst_size, src was truncated.
    *
    * @note If dst_size is 0, nothing is written to dst and the length of 
    * src is returned.
    * @warning dst and src must be valid non-null pointers.
    */
   size_t strcpy( char *dst, size_t dst_size, const char *src );

   uint32_t tid( );
   uint64_t now_ns( );

}