// Copyright (c) 2015 Nuxi, https://nuxi.nl/
//
// This file is distrbuted under a 2-clause BSD license.
// See the LICENSE file for details.

#include <string.h>

void *memchr(const void *s, int c, size_t n) {
  const unsigned char *sb = s;
  while (n-- > 0) {
    if (*sb == (unsigned char)c)
      return (void *)sb;
    ++sb;
  }
  return NULL;
}
