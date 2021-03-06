//=======================================================================
// Copyright Baptiste Wicht 2013-2014.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//=======================================================================

#ifndef SLEEP_QUEUE_H
#define SLEEP_QUEUE_H

#include <queue.hpp>
#include <lock_guard.hpp>

#include "spinlock.hpp"
#include "scheduler.hpp"

#include "console.hpp"

struct sleep_queue {
private:
    mutable spinlock lock;

    std::queue<scheduler::pid_t> queue;

public:
    bool empty() const {
        std::lock_guard<spinlock> l(lock);

        return queue.empty();
    }

    scheduler::pid_t top_process() const {
        std::lock_guard<spinlock> l(lock);

        return queue.top();
    }

    scheduler::pid_t wake_up(){
        std::lock_guard<spinlock> l(lock);

        //Get the first process
        auto pid = queue.top();

        //Remove the process from the queue
        queue.pop();

        //Indicate to the scheduler that this process will be able
        //to run
        scheduler::unblock_process(pid);

        return pid;
    }

    void sleep(){
        lock.acquire();

        //Get the current process information
        auto pid = scheduler::get_pid();

        //Enqueue the process in the sleep queue
        queue.push(pid);

        lock.release();

        //This process will sleep
        scheduler::block_process(pid);
    }
};

#endif
