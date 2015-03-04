// Copyright (c) 2015 Nuxi, https://nuxi.nl/
//
// This file is distrbuted under a 2-clause BSD license.
// See the LICENSE file for details.

#include <common/syscalldefs.h>

#include <assert.h>
#include <pthread.h>
#include <stdatomic.h>

int pthread_cond_destroy(pthread_cond_t *cond) {
  assert(atomic_load_explicit(&cond->__waiters, memory_order_relaxed) ==
             CLOUDABI_CONDVAR_HAS_NO_WAITERS &&
         "Attempted to destroy a condition variable with blocked threads");
  return 0;
}
