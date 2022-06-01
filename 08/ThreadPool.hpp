#pragma once

#include <iostream>
#include <vector>
#include <queue>
#include <any>
#include <unistd.h>
#include <future>
#include <atomic>
#include <mutex>
#include <utility>
#include <functional>
#include <type_traits>


namespace custom_t_pool {
	class ThreadPool {
		std::vector<std::thread> threads;
		std::queue<std::function<void()>> task_q;
		size_t threads_count;
		std::atomic<bool> stop;
		int sleep_duration = 1000;
		mutable std::mutex queue_mutex;
	public:
		explicit ThreadPool(size_t poolSize);
		~ThreadPool();
		
		// pass arguments by value
		template <class Func, class... Args>
		auto exec(Func func, Args... args) -> std::future<decltype(func(args...))>;
	private:
		bool pop_task(std::function<void()>&);
		void make_threads();
		void join_threads();
		void thread_sleep() const;
		void worker_target();
	};
}
#include "ThreadPool.tpp"
