// Copyright (c) 2015 Nuxi, https://nuxi.nl/
//
// SPDX-License-Identifier: BSD-2-Clause

#include <pthread.h>
#include <string.h>

#include "stdatomic_impl.h"

void __atomic_store(size_t len, void *object, void *value, memory_order order) {
  pthread_rwlock_t *lock = atomic_fallback_getlock(object);
  pthread_rwlock_wrlock(lock);
  memcpy(object, value, len);
  pthread_rwlock_unlock(lock);
}
