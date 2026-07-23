/*
 * threadsafequeue.hpp
 *
 *  Created on: Jul 23, 2026
 *      Author: pjarnot
 */

#ifndef NSC_SEARCH_INCLUDE_UTILS_THREADSAFEQUEUE_HPP_
#define NSC_SEARCH_INCLUDE_UTILS_THREADSAFEQUEUE_HPP_


#include <queue>
#include <mutex>
#include <condition_variable>

template<typename T>
class ThreadSafeQueue {
private:
    std::queue<T> queue;
    std::mutex mtx;
    std::condition_variable cond_var;

public:
    // Push an item into the queue
    void push(T value) {
        // Lock the mutex before modifying the queue
        std::lock_guard<std::mutex> lock(mtx);
        queue.push(std::move(value));

        // Notify one waiting thread that new data is available
        cond_var.notify_one();
    }

    // Wait until an item is available, then pop it
    void wait_and_pop(T& value) {
        // Use unique_lock because condition_variable requires it to unlock/relock internally
        std::unique_lock<std::mutex> lock(mtx);

        // Wait until the queue is not empty.
        // The lock is released while waiting and re-acquired when awakened.
        cond_var.wait(lock, [this]{ return !queue.empty(); });

        value = std::move(queue.front());
        queue.pop();
    }

    // Attempt to pop an item without waiting (returns false if empty)
    bool try_pop(T& value) {
        std::lock_guard<std::mutex> lock(mtx);
        if(queue.empty()) {
            return false;
        }
        value = std::move(queue.front());
        queue.pop();
        return true;
    }

    // Check if empty (must also be locked!)
    bool empty() {
        std::lock_guard<std::mutex> lock(mtx);
        return queue.empty();
    }
};



#endif /* NSC_SEARCH_INCLUDE_UTILS_THREADSAFEQUEUE_HPP_ */
