// Copyright (c) 2015 Nuxi, https://nuxi.nl/
//
// This file is distrbuted under a 2-clause BSD license.
// See the LICENSE file for details.

#ifndef COMMON_FLOAT_H
#define COMMON_FLOAT_H

#include <locale.h>
#include <stdbool.h>
#include <stdint.h>
#include <wchar.h>

// A base-2 floating point number. The value associated with a number
// in this structure is equal to:
//
//     (significand[0] << 64 | significand[1]) * 2^exponent
struct float2 {
  uint64_t significand[2];
  int exponent;
  int flags;
#define F2_INFINITE 0x1
#define F2_NEGATIVE 0x2
#define F2_NAN 0x4
};

// A base-10 floating point number. The value associated with a number
// in this structure is equal to:
//
//     (significand[0] << 64 | significand[1]) * 10^exponent
struct float10 {
  uint64_t significand[2];
  int exponent;
};

// Normalize.
void __float2_normalize(struct float2 *);

// Conversion between float2 and float.
bool __float2_to_float(const struct float2 *, float *);
#if 0  // Not needed.
void __float_to_float2(float, struct float2 *);
#endif

// Conversion between float2 and double.
bool __float2_to_double(const struct float2 *, double *);
#if 0  // Not needed.
void __double_to_float2(double, struct float2 *);
#endif

// Conversion between float2 and long double.
bool __float2_to_long_double(const struct float2 *, long double *);
void __long_double_to_float2(long double, struct float2 *);

// Conversion between float2 and float10.
int __float2_to_float10(const struct float2 *, struct float10 *);
int __float10_to_float2(const struct float10 *, struct float2 *);

// Parsing of strings with floating point literals.
bool __strtofloat2(const char *restrict, char **restrict, locale_t,
                   struct float2 *);
bool __wcstofloat2(const wchar_t *restrict, wchar_t **restrict, locale_t,
                   struct float2 *);

#endif
