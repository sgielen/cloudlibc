// Copyright (c) 2015 Nuxi, https://nuxi.nl/
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

// <arpa/inet.h> - definitions for internet operations
//
// Features missing:
// - inet_ntoa():
//   Not thread-safe.
// - inet_addr():
//   No IPv6 support. Use inet_pton() instead.

#ifndef _ARPA_INET_H_
#define _ARPA_INET_H_

#include <_/struct/in_addr.h>
#include <_/types.h>

typedef __in_addr_t in_addr_t;
typedef __in_port_t in_port_t;
typedef __uint16_t uint16_t;
typedef __uint32_t uint32_t;

#define INET_ADDRSTRLEN 16
#define INET6_ADDRSTRLEN 46

__BEGIN_DECLS
uint32_t htonl(uint32_t) __pure2;
uint16_t htons(uint16_t) __pure2;
uint32_t ntohl(uint32_t) __pure2;
uint16_t ntohs(uint16_t) __pure2;
const char *inet_ntop(int, const void *__restrict, char *__restrict, __size_t);
int inet_pton(int, const char *__restrict, void *__restrict);
__END_DECLS

#endif
