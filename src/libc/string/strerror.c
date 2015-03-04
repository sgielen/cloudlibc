// Copyright (c) 2015 Nuxi, https://nuxi.nl/
//
// This file is distrbuted under a 2-clause BSD license.
// See the LICENSE file for details.

#include <locale.h>
#include <string.h>

char *strerror(int errnum) {
  return strerror_l(errnum, LC_GLOBAL_LOCALE);
}
