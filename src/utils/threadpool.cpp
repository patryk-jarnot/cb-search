/*
 * threadpool.cpp
 *
 *  Created on: Nov 13, 2021
 *      Author: pjarnot
 */

#include "utils/threadpool.hpp"

#include "debug.hpp"

#include <iostream>



ThreadPool::ThreadPool(int ithread_count) {
	if (ithread_count == 0) {
		thread_count = std::thread::hardware_concurrency();
	}
	else {
		thread_count = ithread_count;
	}
	terminate = false;
	stopped = false;
	construct();
}


ThreadPool::ThreadPool() {
	thread_count = std::thread::hardware_concurrency();
	terminate = false;
	stopped = false;
}


void ThreadPool::construct() {
	for (int i = 0; i < thread_count; ++i)
		workers.emplace_back([this, i] {
			{
				std::unique_lock < std::mutex > lock(this->worker_id_mutex);
				this->worker_ids[std::hash<std::thread::id>{}(std::this_thread::get_id())] = i;
			}
			while (true) {
				std::function < void() > task;

				{
					std::unique_lock < std::mutex > lock(this->queue_mutex);
					this->condition.wait(lock, [this] {
						return !this->tasks.empty() || this->terminate;
					});
					if (this->tasks.empty() && this->terminate)
						return;
					task = std::move(this->tasks.front());
					this->tasks.pop();
				}

				task();
			}
		}
		);
}


ThreadPool::~ThreadPool() {
	if (stopped == false) {
		dispose();
	}
}


void ThreadPool::dispose() {
    {
        std::unique_lock<std::mutex> lock(queue_mutex);
        terminate = true;
    }
    condition.notify_all();
    for(std::thread &worker: workers)
        worker.join();

    stopped = true;
}




int function_thread(int i) {
	std::cout << "hello " << i << std::endl;
	std::this_thread::sleep_for(std::chrono::seconds(1));
	std::cout << "world " << i << std::endl;
	return i*i;
}

void test_threadpool() {
    ThreadPool pool(4);
    std::vector< std::future<int> > results;

    for(int i = 0; i < 8; ++i) {
        results.emplace_back(
        		pool.enqueue(function_thread, i)
        );
    }

    for(auto && result: results)
        std::cout << result.get() << ' ';
    std::cout << std::endl;
}





