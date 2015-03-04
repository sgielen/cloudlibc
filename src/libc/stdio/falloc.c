// Copyright (c) 2015 Nuxi, https://nuxi.nl/
//
// This file is distrbuted under a 2-clause BSD license.
// See the LICENSE file for details.

#include <common/stdio.h>

#include <errno.h>
#include <pthread.h>
#include <stdlib.h>

FILE *__falloc(const char *mode, locale_t locale) {
  // Parse mode.
  int oflags = get_oflags_from_string(mode);
  if (oflags == 0) {
    errno = EINVAL;
    return NULL;
  }

  // Create file object.
  FILE *file = calloc(1, sizeof(*file));
  if (file == NULL)
    return NULL;
  file->fd = -1;
  file->oflags = oflags;
  file->ctype = locale->ctype;
  file->buftype = _IOFBF;

  // Initialize object lock. The lock needs to be recursive, as it
  // should still be possible to call arbitrary stdio functions after
  // flockfile() has been called.
  pthread_mutexattr_t attr;
  if (pthread_mutexattr_init(&attr) != 0) {
    free(file);
    errno = ENOMEM;
    return NULL;
  }
  pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
  if (pthread_mutex_init(&file->lock, &attr) != 0) {
    free(file);
    pthread_mutexattr_destroy(&attr);
    errno = ENOMEM;
    return NULL;
  }
  pthread_mutexattr_destroy(&attr);
  return file;
}
