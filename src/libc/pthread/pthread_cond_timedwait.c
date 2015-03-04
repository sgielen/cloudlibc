// Copyright (c) 2015 Nuxi, https://nuxi.nl/
//
// This file is distrbuted under a 2-clause BSD license.
// See the LICENSE file for details.

#include <common/crt.h>
#include <common/pthread.h>
#include <common/syscalls.h>
#include <common/time.h>

#include <assert.h>
#include <errno.h>
#include <pthread.h>

int pthread_cond_timedwait(pthread_cond_t *restrict cond,
                           __pthread_lock_t *restrict lock,
                           const struct timespec *restrict abstime) {
  assert((atomic_load_explicit(&lock->__state, memory_order_relaxed) &
          ~CLOUDABI_LOCK_KERNEL_MANAGED) ==
             (__pthread_thread_id | CLOUDABI_LOCK_WRLOCKED) &&
         "This lock is not write-locked by this thread");
  assert(lock->__write_recursion <= 0 &&
         "Cannot wait using a write recursive lock");

  // Call into the kernel to wait on the condition variable.
  cloudabi_event_t events[2] = {
      {
       .type = CLOUDABI_EVENT_TYPE_CONDVAR,
       .condvar.condvar = &cond->__waiters,
       .condvar.lock = &lock->__state,
      },
      {
       .type = CLOUDABI_EVENT_TYPE_CLOCK, .clock.clock_id = cond->__clock,
      },
  };
  if (!timespec_to_timestamp_clamp(abstime, &events[1].clock.timeout))
    return EINVAL;
  size_t triggered;

  // Remove lock from lock list while blocking.
  LIST_REMOVE(lock, __write_locks);
  cloudabi_errno_t error =
      cloudabi_sys_poll_once(events, 2, events, 2, &triggered);
  LIST_INSERT_HEAD(&__pthread_wrlocks, lock, __write_locks);

  if (error != 0)
    __pthread_terminate(error, "Failed to wait on condition variable");
  for (size_t i = 0; i < triggered; ++i) {
    if (events[i].type == CLOUDABI_EVENT_TYPE_CONDVAR) {
      if (events[i].error != 0)
        __pthread_terminate(events[i].error,
                            "Failed to wait on condition variable");
      return 0;
    }
  }
  return ETIMEDOUT;
}
