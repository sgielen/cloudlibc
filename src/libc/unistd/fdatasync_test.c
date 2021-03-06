// Copyright (c) 2015-2017 Nuxi, https://nuxi.nl/
//
// SPDX-License-Identifier: BSD-2-Clause

#include <errno.h>
#include <fcntl.h>
#include <testing.h>
#include <unistd.h>

TEST(fdatasync, bad) {
  ASSERT_EQ(-1, fdatasync(-123));
  ASSERT_EQ(EBADF, errno);
}

TEST(fdatasync, example) {
  int fd = openat(fd_tmp, "file", O_CREAT | O_RDWR);
  ASSERT_LE(0, fd);
  ASSERT_EQ(0, fdatasync(fd));
  ASSERT_EQ(0, close(fd));
}
