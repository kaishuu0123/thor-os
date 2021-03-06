//=======================================================================
// Copyright Baptiste Wicht 2013-2014.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//=======================================================================

#ifndef KERNEL_UTILS_H
#define KERNEL_UTILS_H

#include <types.hpp>

uint8_t in_byte(uint16_t _port);
void out_byte(uint16_t _port, uint8_t _data);

uint16_t in_word(uint16_t _port);
void out_word(uint16_t _port, uint16_t _data);

void print_stack(const char* msg, size_t check);
#define SHOW_STACK(M) { size_t check = 0; asm volatile("mov %0, rsp;" : "=r" (check)); print_stack(((M)), check); }

#endif
