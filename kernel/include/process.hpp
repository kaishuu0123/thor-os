//=======================================================================
// Copyright Baptiste Wicht 2013-2014.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//=======================================================================

#ifndef PROCESS_H
#define PROCESS_H

#include <types.hpp>
#include <vector.hpp>

#include "paging.hpp"
#include "interrupts.hpp"

namespace scheduler {

constexpr const size_t MAX_PRIORITY = 4;
constexpr const size_t MIN_PRIORITY = 1;
constexpr const size_t PRIORITY_LEVELS = MAX_PRIORITY - MIN_PRIORITY + 1;
constexpr const size_t DEFAULT_PRIORITY = 3;

typedef size_t pid_t;

struct segment_t {
    size_t physical;
    size_t size;
};

struct process_t {
    pid_t pid;
    pid_t ppid;

    bool system;

    size_t priority;

    size_t tty;

    size_t physical_cr3;
    size_t paging_size;

    size_t physical_user_stack;
    size_t physical_kernel_stack;
    size_t virtual_kernel_stack;

    size_t kernel_rsp;

    size_t brk_start;
    size_t brk_end;

    volatile interrupt::syscall_regs* context;

    std::vector<segment_t> segments;
};

constexpr const size_t program_base = 0x8000000000;
constexpr const size_t program_break = 0x9000000000;

constexpr const auto user_stack_size = 2 * paging::PAGE_SIZE;
constexpr const auto kernel_stack_size = 2 * paging::PAGE_SIZE;

constexpr const auto user_stack_start = program_base + 0x700000;
constexpr const auto user_rsp = user_stack_start + (user_stack_size - 8);

} //end of namespace scheduler

#endif
