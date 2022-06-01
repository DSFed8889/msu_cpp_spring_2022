#include <iostream>
#include <thread>
#include <sstream>
#include <unistd.h>
#include <string>
#include <typeinfo>
#include <gtest/gtest.h>
#include "ThreadPool.hpp"

using namespace custom_t_pool;

class TestThreadPool : public ::testing::Test {
};

TEST_F(TestThreadPool, test_new_thread) {
	ThreadPool pool(std::thread::hardware_concurrency());
	std::future<std::thread::id> f = pool.exec([](){return std::this_thread::get_id();});
	ASSERT_NE(std::this_thread::get_id(), f.get());
}

TEST_F(TestThreadPool, test_parallel_working) {
	size_t threads_count = std::thread::hardware_concurrency();
	ThreadPool pool(threads_count);
	std::vector<std::future<void>> futures;
	std::vector<std::future_status> statuses;
	for (size_t i = 0; i < threads_count; i++)
		futures.push_back(pool.exec([](){std::this_thread::sleep_for(std::chrono::seconds(2));}));
	std::this_thread::sleep_for(std::chrono::seconds(3));
	for (size_t i = 0; i < threads_count; i++)
		ASSERT_EQ(futures[i].wait_for(std::chrono::seconds(0)), std::future_status::ready);
}

TEST_F(TestThreadPool, test_zero_threads) {
	ThreadPool pool(0);
	std::future<void> f = pool.exec([](){return;});
	ASSERT_EQ(f.wait_for(std::chrono::seconds(5)), std::future_status::timeout);
}

class A {
	int a;
public:
	A(int i): a(i){}
	bool operator == (const A& A) const {
		return a == A.a;
	}
};

TEST_F(TestThreadPool, test_tasks_more_then_threads) {
	size_t threads_count = std::thread::hardware_concurrency();
	ThreadPool pool(threads_count);
	std::vector<std::future<void>> futures;
	for (size_t i = 0; i < threads_count + 2; i++)
		futures.push_back(pool.exec([](){std::this_thread::sleep_for(std::chrono::milliseconds(100));}));
	std::chrono::system_clock::time_point second_passed = std::chrono::system_clock::now() + std::chrono::seconds(1);
	for (size_t i = 0; i < threads_count + 2; i++)
		ASSERT_EQ(futures[i].wait_until(second_passed), std::future_status::ready);
}

TEST_F(TestThreadPool, test_different_types) {
	ThreadPool pool(2);
	std::future<int> f1 = pool.exec([](){return 100;});
	std::future<std::string> f2 = pool.exec([](){return std::string("Completed");});
	std::future<class A> f3 = pool.exec([](){return A(8);});
	ASSERT_EQ(f1.get(), 100);
	ASSERT_EQ(f2.get(), std::string("Completed"));
	ASSERT_EQ(f3.get(), A(8));
}


int main(int argc, char *argv[]) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}