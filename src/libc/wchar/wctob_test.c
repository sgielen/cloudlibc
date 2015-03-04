// Copyright (c) 2015 Nuxi, https://nuxi.nl/
//
// This file is distrbuted under a 2-clause BSD license.
// See the LICENSE file for details.

#include <locale.h>
#include <stdio.h>
#include <testing.h>
#include <wchar.h>

TEST(wctob, ascii) {
  // WEOF should map to EOF.
  ASSERT_EQ(EOF, wctob(WEOF));
  ASSERT_EQ(EOF, wctob_l(WEOF, LC_POSIX_UNICODE_LOCALE));

  // All lower codepoints should be mapped.
  for (wint_t i = 0; i < 128; ++i) {
    SCOPED_NOTE(i, {
      ASSERT_EQ(i, wctob(i));
      ASSERT_EQ(i, wctob_l(i, LC_POSIX_UNICODE_LOCALE));
    });
  }
  // Everything above should throw EOF.
  for (wint_t i = 128; i < 1000; ++i) {
    SCOPED_NOTE(i, {
      ASSERT_EQ(EOF, wctob(i));
      ASSERT_EQ(EOF, wctob_l(i, LC_POSIX_UNICODE_LOCALE));
    });
  }
}

TEST(wctob, iso_8859_1) {
  locale_t locale = newlocale(LC_CTYPE_MASK, ".ISO-8859-1", 0);
  ASSERT_NE(NULL, locale);

  // WEOF should map to EOF.
  ASSERT_EQ(EOF, wctob_l(WEOF, locale));

  // All lower codepoints should be mapped.
  for (wint_t i = 0; i < 256; ++i) {
    SCOPED_NOTE(i, { ASSERT_EQ(i, wctob_l(i, locale)); });
  }
  // Everything above should throw EOF.
  for (wint_t i = 256; i < 1000; ++i) {
    SCOPED_NOTE(i, { ASSERT_EQ(EOF, wctob_l(i, locale)); });
  }

  freelocale(locale);
}
