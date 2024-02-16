
/**
 * `b64.h' - b64
 *
 * copyright (c) 2014 joseph werle
 */

#ifndef B64_H
#define B64_H 1

typedef struct b64_buffer {
    char *ptr;
    int bufc;
} b64_buffer_t;

/**
 *  Memory allocation functions to use. You can define b64_malloc and
 * b64_realloc to custom functions if you want.
 */

#ifndef b64_malloc
#define b64_malloc(ptr) malloc(ptr)
#endif
#ifndef b64_realloc
#define b64_realloc(ptr, size) realloc(ptr, size)
#endif

// How much memory to allocate per buffer
#define B64_BUFFER_SIZE (1024 * 64) // 64K

// Start buffered memory
int b64_buf_malloc(b64_buffer_t *buffer);

// Update memory size. Returns the same pointer if we
// have enough space in the buffer. Otherwise, we add
// additional buffers.
int b64_buf_realloc(b64_buffer_t *buffer, size_t size);

/**
 * Base64 index table.
 */

static const char b64_table[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

/**
 * Decode `char *' source with `size_t' size.
 * Returns a `unsigned char *' base64 decoded string.
 */
unsigned char *b64_decode(const char *, size_t);

/**
 * Decode `char *' source with `size_t' size.
 * Returns a `unsigned char *' base64 decoded string + size of decoded string.
 */
unsigned char *b64_decode_ex(const char *, size_t, size_t *);

#endif
