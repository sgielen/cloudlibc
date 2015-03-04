// Copyright (c) 2015 Nuxi, https://nuxi.nl/
//
// This file is distrbuted under a 2-clause BSD license.
// See the LICENSE file for details.

#include <fenv.h>

#include "fenv_impl.h"

int feholdexcept(fenv_t *envp) {
  // Save x87 and SSE state.
  fnstenv(&envp->__x87);
  envp->__mxcsr = stmxcsr();

  // Clear x87 floating-point exceptions. There is no need to mask
  // floating-point exceptions, as this is already done by fnstenv().
  fnclex();

  // Clear SSE floating-point exceptions. Also mask all exceptions.
  uint32_t mxcsr = envp->__mxcsr;
  mxcsr &= ~FE_ALL_EXCEPT;
  mxcsr |= FE_ALL_EXCEPT << EXCEPTION_MASK_SHIFT;
  ldmxcsr(mxcsr);

  return 0;
}
