#include "ThreadPool.hpp"

namespace custom_t_pool {
	
	ThreadPool::ThreadPool([[maybe_unused]] size_t poolSize) {
		stop = false;
		
		threads_count = poolSize;
		make_threads();
	}
	
	void ThreadPool::make_threads() {
		for (size_t i = 0; i < threads_count; i++)
			threads.push_back(std::thread(&ThreadPool::worker_target, this));
	}
	
	void ThreadPool::join_threads() {
		for (size_t i = 0; i < threads_count; i++)
			threads[i].join();
	}
	
	void ThreadPool::worker_target()  {
		while (!stop) {
			std::function<void()> task = [](){};
			if (pop_task(task))
				task();
			else
				thread_sleep();
		}
	}
	
	bool ThreadPool::pop_task(std::function<void()>& task) {
		const std::scoped_lock lock(queue_mutex);
		if (task_q.empty())
			return false;
		else {
			task = task_q.front();
			task_q.pop();
			return true;
		}
	}
	
	ThreadPool::~ThreadPool() {
		stop = true;
		join_threads();
	}
	
	void ThreadPool::thread_sleep() const {
		if (sleep_duration)
			std::this_thread::sleep_for(std::chrono::microseconds(sleep_duration));
		else
			std::this_thread::yield();
	}
	
}