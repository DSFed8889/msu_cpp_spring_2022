#pragma once

#include "ThreadPool.hpp"

namespace custom_t_pool {
	
	template <class Func, class... Args>
	auto ThreadPool::exec(Func func, Args... args) -> std::future<decltype(func(args...))> {
		auto task = std::make_shared<std::packaged_task<typename std::result_of<Func(Args...)>::type()>>(std::bind(func, args...));
		const std::scoped_lock lock(queue_mutex);
		task_q.push([task] { (*task)(); });
		return task->get_future();
	}
}