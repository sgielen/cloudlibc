// Copyright (c) 2015 Nuxi, https://nuxi.nl/
//
// This file is distrbuted under a 2-clause BSD license.
// See the LICENSE file for details.

#include <common/syscalls.h>

#include <errno.h>
#include <unistd.h>

int ftruncate(int fildes, off_t length) {
  if (length < 0) {
    errno = EINVAL;
    return -1;
  }
  cloudabi_filestat_t fs = {
      .st_size = length,
  };
  cloudabi_errno_t error =
      cloudabi_sys_file_stat_fput(fildes, &fs, CLOUDABI_FILESTAT_SIZE);
  if (error != 0) {
    errno = error;
    return -1;
  }
  return 0;
}
