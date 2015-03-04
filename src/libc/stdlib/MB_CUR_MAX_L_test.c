// Copyright (c) 2015 Nuxi, https://nuxi.nl/
//
// This file is distrbuted under a 2-clause BSD license.
// See the LICENSE file for details.

#include <locale.h>
#include <stdlib.h>
#include <testing.h>

TEST(MB_CUR_MAX_L, examples) {
  ASSERT_EQ(1, MB_CUR_MAX_L(LC_POSIX_LOCALE));
  ASSERT_EQ(4, MB_CUR_MAX_L(LC_POSIX_UNICODE_LOCALE));
}
