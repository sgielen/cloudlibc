// Copyright (c) 2015 Nuxi, https://nuxi.nl/
//
// This file is distrbuted under a 2-clause BSD license.
// See the LICENSE file for details.

#include <common/stdio.h>

#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

size_t fread(void *restrict ptr, size_t size, size_t nitems,
             FILE *restrict stream) {
  // Zero-sized read. Return immediately.
  if (size == 0 || nitems == 0)
    return 0;

  // Check for overflow of size * nitems.
  if (nitems > SIZE_MAX / size) {
    flockfile(stream);
    stream->flags |= F_ERROR;
    funlockfile(stream);
    errno = EINVAL;
    return 0;
  }

  char *outbuf = ptr;
  size_t outbuflen = size * nitems;
  flockfile(stream);
  for (;;) {
    // Obtain the read buffer.
    const char *readbuf;
    size_t readbuflen;
    if (!fread_peek(stream, &readbuf, &readbuflen) || readbuflen == 0) {
      funlockfile(stream);
      return (outbuf - (char *)ptr) / size;
    }

    // Last buffer. Consume it, likely partially, and return.
    if (outbuflen <= readbuflen) {
      memcpy(outbuf, readbuf, outbuflen);
      fread_consume(stream, outbuflen);
      funlockfile(stream);
      return nitems;
    }

    // Fully consume the read buffer and obtain the next one.
    memcpy(outbuf, readbuf, readbuflen);
    outbuf += readbuflen;
    outbuflen -= readbuflen;
    fread_consume(stream, readbuflen);
  }
}
