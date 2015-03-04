// Copyright (c) 2015 Nuxi, https://nuxi.nl/
//
// This file is distrbuted under a 2-clause BSD license.
// See the LICENSE file for details.

#include <locale.h>
#include <stdio.h>
#include <testing.h>
#include <wchar.h>

TEST(btowc, ascii) {
  // EOF should map to WEOF.
  ASSERT_EQ(WEOF, btowc(EOF));
  ASSERT_EQ(WEOF, btowc_l(EOF, LC_POSIX_UNICODE_LOCALE));

  // All lower codepoints should be mapped.
  for (int i = 0; i < 128; ++i) {
    SCOPED_NOTE(i, {
      ASSERT_EQ(i, btowc(i));
      ASSERT_EQ(i, btowc_l(i, LC_POSIX_UNICODE_LOCALE));
    });
  }
  // Everything above should throw WEOF.
  for (int i = 128; i < 256; ++i) {
    SCOPED_NOTE(i, {
      ASSERT_EQ(WEOF, btowc(i));
      ASSERT_EQ(WEOF, btowc_l(i, LC_POSIX_UNICODE_LOCALE));
    });
  }
}

TEST(btowc, iso_8859_1) {
  locale_t locale = newlocale(LC_CTYPE_MASK, ".ISO-8859-1", 0);
  ASSERT_NE(NULL, locale);

  // EOF should map to WEOF.
  ASSERT_EQ(WEOF, btowc_l(EOF, locale));

  // All lower codepoints should be mapped.
  for (int i = 0; i < 256; ++i) {
    SCOPED_NOTE(i, { ASSERT_EQ(i, btowc_l(i, locale)); });
  }

  freelocale(locale);
}
