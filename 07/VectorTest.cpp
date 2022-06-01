#include <string>
#include <vector>
#include <iterator>
#include <memory>
#include <initializer_list>
#include <gtest/gtest.h>

#include "Vector.hpp"

using namespace customVector;


class TestVector : public ::testing::Test {};


TEST_F(TestVector, test_ctr) {
	ASSERT_NO_THROW(Vector<size_t>{});
	ASSERT_NO_THROW(Vector<std::string>(10));
	ASSERT_NO_THROW(Vector<char>(10, 'a'));
	ASSERT_NO_THROW(Vector<int>({5, 10, 2, 7}));
	ASSERT_NO_THROW(Vector<int>(Vector<int>({5, 10, 2, 7})));
}


TEST_F(TestVector, test_assign_op) {
	Vector<int> vec = {1, 2, 3, 4};
	Vector<int> v2(1);
	v2 = vec;
	ASSERT_EQ(vec.size(), v2.size());
	for (size_t i = 0; i < vec.size(); ++i)
	ASSERT_EQ(vec[i], v2[i]);
}


TEST_F(TestVector, test_access_op) {
	Vector<int> vec(10);
	for (size_t i = 0; i < vec.size(); ++i)
		vec[i] = i;
	for (size_t i = 0; i < vec.size(); ++i)
		ASSERT_EQ(vec[i], i);
}


TEST_F(TestVector, test_push_back) {
	Vector<int> vec(10);
	for(size_t i = 0; i < 5; ++i)
	vec.push_back(i);
	for (size_t i = 0; i < 5; ++i)
	ASSERT_EQ(vec[i], i);
	ASSERT_EQ(vec.size(), 5);
	
	Vector<int> v2(10);
	for(size_t i = 0; i < 15; ++i)
	v2.push_back(-i);
	for (size_t i = 0; i < 15; ++i)
	ASSERT_EQ(v2[i], -i);
	ASSERT_EQ(v2.size(), 15);
}


TEST_F(TestVector, test_pop_back) {
	Vector<unsigned> vec(10);
	for(size_t i = 0; i < 15; ++i)
	vec.push_back(i);
	for (size_t i = 0; i < 15; ++i)
	ASSERT_EQ(vec[i], i);
	ASSERT_EQ(vec.size(), 15);
	
	for(size_t i = 0; i < 5; ++i)
	vec.pop_back();
	ASSERT_EQ(vec.size(), 10);
}


TEST_F(TestVector, test_emplace_back) {
	Vector<char*> vec(10);
	for(size_t i = 0; i < 15; ++i)
		vec.emplace_back("Hello, world");
	for (size_t i = 0; i < 15; ++i)
		ASSERT_EQ(vec[i], "Hello, world");
	ASSERT_EQ(vec.size(), 15);
}


TEST_F(TestVector, test_empty) {
	Vector<unsigned> vec(10);
	ASSERT_TRUE(vec.empty());
	
	for(size_t i = 0; i < 15; ++i)
	vec.push_back(i);
	ASSERT_FALSE(vec.empty());
	
	for(size_t i = 0; i < 15; ++i)
	vec.pop_back();
	ASSERT_TRUE(vec.empty());
}


TEST_F(TestVector, test_size) {
	Vector<unsigned> vec(10, 0);
	ASSERT_EQ(vec.size(), 10);
	for(size_t i = 0; i < 15; ++i)
	vec.push_back(i);
	ASSERT_EQ(vec.size(), 25);
	
	for(size_t i = 0; i < 5; ++i)
	vec.pop_back();
	ASSERT_EQ(vec.size(), 20);
}


TEST_F(TestVector, test_clear) {
	Vector<unsigned> vec(10);
	for(size_t i = 0; i < 15; ++i)
	vec.push_back(i);
	ASSERT_EQ(vec.size(), 15);
	ASSERT_EQ(vec.capacity(), 16);
	
	vec.clear();
	ASSERT_EQ(vec.size(), 0);
	ASSERT_EQ(vec.capacity(), 0);
	
	for(size_t i = 0; i < 15; ++i)
	vec.push_back(i);
	ASSERT_EQ(vec.size(), 15);
	ASSERT_EQ(vec.capacity(), 16);
}


TEST_F(TestVector, test_iterator) {
	Vector<unsigned> vec(10);
	for(size_t i = 0; i < 15; ++i)
	vec.push_back(i);
	
	auto v_begin = vec.begin();
	auto v_rbegin = vec.rbegin();
	auto v_end = vec.end();
	auto v_rend = vec.end();
	
	size_t i = 0;
	for (auto it = v_begin; it < v_end; ++it)
	ASSERT_EQ(*it, i++);
	
	i = 14;
	for (auto it = v_rbegin; it > v_rend; --it)
	ASSERT_EQ(*it, i--);
}


TEST_F(TestVector, test_resize) {
	Vector<signed> vec{};
	vec.resize(10);
	ASSERT_EQ(vec.capacity(), 16);
	ASSERT_EQ(vec.size(), 0);
	
	for(size_t i = 0; i < 25; ++i)
	vec.push_back(i);
	ASSERT_EQ(vec.capacity(), 32);
	ASSERT_EQ(vec.size(), 25);
	
	vec.resize(40);
	ASSERT_EQ(vec.capacity(), 64);
	ASSERT_EQ(vec.size(), 25);
	
	vec.resize(10);
	ASSERT_EQ(vec.capacity(), 16);
	ASSERT_EQ(vec.size(), 10);
	for (size_t i = 0; i < 10; ++i)
	ASSERT_EQ(vec[i], i);
}


TEST_F(TestVector, test_reserve) {
	Vector<short> vec(10);
	ASSERT_EQ(vec.capacity(), 16);
	
	vec.reserve(10);
	ASSERT_EQ(vec.capacity(), 32);
	
	vec.reserve(20);
	ASSERT_EQ(vec.capacity(), 64);
}


TEST_F(TestVector, test_capacity) {
	Vector<short> vec(10);
	ASSERT_EQ(vec.capacity(), 16);
	for(size_t i = 0; i < 25; ++i)
	vec.push_back(i);
	ASSERT_EQ(vec.capacity(), 32);
	
	for(size_t i = 0; i < 20; ++i)
	vec.pop_back();
	ASSERT_EQ(vec.capacity(), 16);
}


int main(int argc, char *argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
