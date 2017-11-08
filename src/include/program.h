// Copyright (c) 2015-2017 Nuxi, https://nuxi.nl/
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions
// are met:
// 1. Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
// 2. Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the
//    documentation and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
// ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
// FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
// DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
// OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
// HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
// LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
// OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
// SUCH DAMAGE.

// <program.h> - execution of programs

#ifndef _PROGRAM_H_
#define _PROGRAM_H_

#include <_/cdefs.h>

#ifndef argdata_t
typedef struct argdata_t argdata_t;
#define argdata_t argdata_t
#endif

__BEGIN_DECLS
int program_exec(int, const argdata_t *);
const char *program_getpid(void);
_Noreturn void program_main(const argdata_t *);
__END_DECLS

// TODO(ed): Remove the deprecated features below.

#define CLD_KILLED 1
#define CLD_EXITED 2

#define WNOHANG 0x1

typedef struct {
  int si_signo;
  int si_code;
  int si_status;
} siginfo_t;

__BEGIN_DECLS
int program_spawn_deprecated(int, const argdata_t *);
int program_wait_deprecated(int, siginfo_t *, int);
__END_DECLS

#endif
