// Copyright (c) 2015 Nuxi, https://nuxi.nl/
//
// This file is distrbuted under a 2-clause BSD license.
// See the LICENSE file for details.

#include <string.h>
#include <testing.h>

TEST(memmove, null) {
  ASSERT_EQ((char *)42, memmove((char *)42, (char *)34, 0));
}

TEST(memmove, example1) {
  char buf[12] = "abcdefghijkl";
  ASSERT_EQ(buf, memmove(buf, buf + 4, 8));
  ASSERT_ARREQ("efghijklijkl", buf, __arraycount(buf));
}

TEST(memmove, example2) {
  char buf[12] = "abcdefghijkl";
  ASSERT_EQ(buf + 4, memmove(buf + 4, buf, 8));
  ASSERT_ARREQ("abcdabcdefgh", buf, __arraycount(buf));
}
