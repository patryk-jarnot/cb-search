/*
 * threadpool.h
 *
 *  Created on: Nov 13, 2021
 *      Author: pjarnot
 */

#ifndef SOURCE_INCLUDE_THREADPOOL_H_
#define SOURCE_INCLUDE_THREADPOOL_H_

#include <thread>
#include <mutex>
#include <queue>
#include <condition_variable>
#include <future>
#include <functional>
#include <map>


class ThreadPool {
public:
	ThreadPool(int ithreadCount);
	ThreadPool();

	~ThreadPool();
	void dispose();

	template<class F, class... Args>
	auto enqueue(F&& f, Args&&... args)
		-> std::future<typename std::result_of<F(Args...)>::type>;

	int get_tasks_count() { return tasks.size(); }

	std::map<size_t, int>* get_worker_ids() { return &worker_ids; }

	void set_thread_count(int ithread_count) { thread_count = ithread_count; }

	void construct();

private:
	int thread_count;

    std::vector< std::thread > workers;
    std::map<size_t, int> worker_ids;
    std::queue< std::function<void()> > tasks;

    // synchronization
    std::mutex queue_mutex;
    std::mutex worker_id_mutex;
    std::condition_variable condition;
    bool terminate;
    bool stopped;


};

void test_threadpool();


template<class F, typename ... Args>
auto ThreadPool::enqueue(F &&f, Args &&... args) -> std::future<typename std::result_of<F(Args...)>::type>
{
	using return_type = typename std::result_of<F(Args...)>::type;

	auto task = std::make_shared<std::packaged_task<return_type()> >(
			std::bind(std::forward<F>(f), std::forward<Args>(args)...));

	std::future<return_type> res = task->get_future();
	{
		std::unique_lock<std::mutex> lock(queue_mutex);

		if (terminate)
			throw std::runtime_error("enqueue on stopped ThreadPool");

		tasks.emplace([task]() {
			(*task)();
		});
	}
	condition.notify_one();
	return res;
}

#endif /* SOURCE_INCLUDE_THREADPOOL_H_ */
