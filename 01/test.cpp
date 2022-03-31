#include <iostream>
#include <gtest/gtest.h>
#include "allocator.hpp"

class TestAllocator : public ::testing::Test {
protected:
	allocator::Allocator allocator;
	void SetUp() {
        std::cout << "SetUp" << std::endl;
	}
	void TearDown() {
        std::cout << "TearDown" << std::endl;
	}
};

TEST_F(TestAllocator, test_alloc) {

	/*"""Testing alloc before makeAllocator"""*/

	ASSERT_EQ(allocator.alloc(0), nullptr);
	ASSERT_EQ(allocator.alloc(1), nullptr);
	allocator.makeAllocator(10);
	ASSERT_EQ(allocator.alloc(0), nullptr);
	ASSERT_NE(allocator.alloc(1), nullptr);

	/*"""Testing alloc returning size"""*/
	
	allocator.makeAllocator(20);
	char* p1 = allocator.alloc(10);
	char* p2 = allocator.alloc(10);
	ASSERT_EQ(p2 - p1, 10);
	
	allocator.makeAllocator(1);
	ASSERT_NE(allocator.alloc(1), nullptr);
	ASSERT_EQ(allocator.alloc(1), nullptr);

	allocator.makeAllocator(50);
	ASSERT_NE(allocator.alloc(20), nullptr);
	ASSERT_NE(allocator.alloc(30), nullptr);
	ASSERT_EQ(allocator.alloc(1), nullptr);


	allocator.makeAllocator(10);
	//Empty 10 bytes
	ASSERT_EQ(allocator.alloc(0), nullptr);
	//Empty 10 bytes
	ASSERT_EQ(allocator.alloc(11), nullptr);
	//Empty 10 bytes (not allocated)
	ASSERT_NE(allocator.alloc(6), nullptr);
	//Empty 4 bytes
	ASSERT_EQ(allocator.alloc(5), nullptr);
	//Empty 4 bytes (not allocated)
	ASSERT_NE(allocator.alloc(4), nullptr);
	//Empty 0 bytes
	ASSERT_EQ(allocator.alloc(1), nullptr);
	//Empty 0 bytes (not allocated)
	ASSERT_EQ(allocator.alloc(0), nullptr);
}

TEST_F(TestAllocator, test_makeAllocator) {

	/*"""Testing of makeallocator creating memory size"""*/

	allocator.makeAllocator(10);
	//Empty 10 bytes
	ASSERT_NE(allocator.alloc(4), nullptr);
	//Empty 6 bytes
	allocator.makeAllocator(20);
	//Empty 20 bytes
	ASSERT_EQ(allocator.alloc(21), nullptr);
	//Empty 20 bytes
	ASSERT_NE(allocator.alloc(20), nullptr);
	//Empty 0 bytes

	/*"""Testing several makeAllocators in a row"""*/

	//Second makeAllocator size is bigger 
	allocator.makeAllocator(10);
	allocator.makeAllocator(10);
	ASSERT_NE(allocator.alloc(10), nullptr);

	//Second makeAllocator size is smaller
	allocator.makeAllocator(20);
	allocator.makeAllocator(5);
	ASSERT_NE(allocator.alloc(5), nullptr);

	//Second makeAllocator size 0
	allocator.makeAllocator(10);
	allocator.makeAllocator(0);
	ASSERT_NE(allocator.alloc(1), nullptr);
}

TEST_F(TestAllocator, test_reset) {
	/*"""Testing that reset is resetting all memory"""*/
	allocator.makeAllocator(50);
	ASSERT_NE(allocator.alloc(20), nullptr);
	ASSERT_NE(allocator.alloc(30), nullptr);
	ASSERT_EQ(allocator.alloc(1), nullptr);
	allocator.reset();
	ASSERT_NE(allocator.alloc(50), nullptr);

	allocator.makeAllocator(10);
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