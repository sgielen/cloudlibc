// Copyright (c) 2015 Nuxi, https://nuxi.nl/
//
// This file is distrbuted under a 2-clause BSD license.
// See the LICENSE file for details.

#include <ctype.h>

int iscntrl(int c) {
  return (c >= '\0' && c < ' ') || c == 0x7f;
}
