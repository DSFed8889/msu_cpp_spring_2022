#include <iostream>
#include <gtest/gtest.h>
#include "allocator.hpp"

class TestAllocator : public ::testing::Test {
protected:
	allocator::Allocator allocator;
	void SetUp() {
        std::cout << "SetUp" << std::endl;
		allocator.makeAllocator(10);
	}
	void TearDown() {
        std::cout << "TearDown" << std::endl;
	}
};

TEST_F(TestAllocator, test_alloc) {
	//Empty 10 bytes
	ASSERT_EQ(allocator.alloc(0), nullptr);
	//Empty 10 bytes
	ASSERT_EQ(allocator.alloc(11), nullptr);
	//Empty 10 bytes (not allocated)
	ASSERT_NE(allocator.alloc(6), nullptr);
	//Empty 4 bytes
	ASSERT_EQ(allocator.alloc(6), nullptr);
	//Empty 4 bytes (not allocated)
	ASSERT_NE(allocator.alloc(4), nullptr);
	//Empty 0 bytes
	ASSERT_EQ(allocator.alloc(0), nullptr);
}

TEST_F(TestAllocator, test_makeAllocator) {
	//Empty 10 bytes
	ASSERT_NE(allocator.alloc(4), nullptr);
	//Empty 6 bytes
	allocator.makeAllocator(20);
	//Empty 20 bytes
	ASSERT_EQ(allocator.alloc(21), nullptr);
	//Empty 20 bytes
	ASSERT_NE(allocator.alloc(20), nullptr);
	//Empty 0 bytes
}

TEST_F(TestAllocator, test_reset) {
	//Empty 10 bytes
	ASSERT_NE(allocator.alloc(4), nullptr);
	//Empty 6 bytes
	allocator.reset();
	//Empty 10 bytes
	ASSERT_EQ(allocator.alloc(11), nullptr);
	//Empty 10 bytes
	ASSERT_NE(allocator.alloc(10), nullptr);
}

int main(int argc, char *argv[]) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}