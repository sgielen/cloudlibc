// Copyright (c) 2015 Nuxi, https://nuxi.nl/
//
// This file is distrbuted under a 2-clause BSD license.
// See the LICENSE file for details.

#include <common/locale.h>

#include <locale.h>
#include <stdarg.h>
#include <wchar.h>

int swprintf(wchar_t *restrict ws, size_t n, const wchar_t *restrict format,
             ...) {
  DEFAULT_LOCALE(locale, LC_CTYPE_MASK | LC_NUMERIC_MASK);
  va_list ap;
  va_start(ap, format);
  int result = vswprintf_l(ws, n, locale, format, ap);
  va_end(ap);
  return result;
}
