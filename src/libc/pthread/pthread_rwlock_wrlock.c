// Copyright (c) 2015 Nuxi, https://nuxi.nl/
//
// This file is distrbuted under a 2-clause BSD license.
// See the LICENSE file for details.

#include <common/pthread.h>
#include <common/syscalls.h>

#include <assert.h>
#include <errno.h>
#include <pthread.h>

int pthread_rwlock_wrlock(pthread_rwlock_t *rwlock) __no_lock_analysis {
  // Attempt to acquire the lock in userspace.
  for (int i = 0; i < LOCK_RETRY_COUNT; ++i) {
    int error = pthread_rwlock_trywrlock(rwlock);
    if (error != EBUSY)
      return error;
  }

  // Call into the kernel to acquire a write lock.
  cloudabi_event_t event = {
      .type = CLOUDABI_EVENT_TYPE_LOCK_WRLOCK, .lock.lock = &rwlock->__state,
  };
  size_t triggered;
  cloudabi_errno_t error =
      cloudabi_sys_poll_once(&event, 1, &event, 1, &triggered);
  if (error != 0)
    __pthread_terminate(error, "Failed to acquire write lock");
  if (event.error != 0)
    __pthread_terminate(event.error, "Failed to acquire write lock");
  assert(rwlock->__write_recursion <= 0 && "Invalid write recursion count");

  // Lock acquired successfully.
  LIST_INSERT_HEAD(&__pthread_wrlocks, rwlock, __write_locks);
  return 0;
}

__strong_reference(pthread_rwlock_wrlock, pthread_mutex_lock);
__strong_reference(pthread_rwlock_wrlock, pthread_spin_lock);
