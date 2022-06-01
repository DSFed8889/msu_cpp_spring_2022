#include <string>
#include <thread>
#include <cstdio>
#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <random>
#include <gtest/gtest.h>

#include "ExtSort.hpp"

using namespace customExtSort;


bool IsSorted(const std::string & input_file) {
	uint64_t cur, prev;
	std::ifstream input(input_file);
	if (!(input.read((char*)&prev, sizeof(prev)))) {
		input.close();
		return true;
	}
	while(input.read((char*)&cur, sizeof(cur))) {
		if(cur < prev) {
			input.close();
			return false;
		}
		prev = cur;
	}
	input.close();
	return true;
}

class TestSort : public ::testing::Test {};


TEST_F(TestSort, test_is_sorted) {
	std::ofstream output1("./output1");
	for (uint64_t i = 0; i < 1000; ++i)
		output1.write((char*)&i, sizeof(i));
	output1.close();
	ASSERT_TRUE(IsSorted("./output1"));
	std::remove("./output1");

	std::ofstream output2("./output2");
	for (uint64_t i = 0; i < 1000; i += 20)
		output2.write((char*)&i, sizeof(i));
	output2.close();
	ASSERT_TRUE(IsSorted("./output2"));
	std::remove("./output2");

	uint64_t val = 15;
	std::ofstream output3("./output3");
	for (uint64_t i = 0; i < 1000; ++i)
	output3.write((char*)&val, sizeof(val));
	output3.close();
	ASSERT_TRUE(IsSorted("./output3"));
	std::remove("./output3");

	std::ofstream out4("./output4");
	for (uint64_t i = 1000; i > 0; --i)
		out4.write((char*)&i, sizeof(i));
	out4.close();
	ASSERT_FALSE(IsSorted("./output4"));
	std::remove("./output4");

	std::ofstream out5("./output5");
	for (uint64_t i = 0; i < 1000; ++i)
		out5.write((char*)&i, sizeof(i));
	out5.write((char*)&val, sizeof(val));
	out5.close();
	ASSERT_FALSE(IsSorted("./output5"));
	std::remove("./output5");
}


TEST_F(TestSort, test_sort)
{
	std::vector<uint64_t> mix;
	for (uint64_t i = 0; i < 1000000; i += 1)
		mix.push_back(i);
	auto rng = std::default_random_engine {};
	std::shuffle(std::begin(mix), std::end(mix), rng);

	std::ofstream output("./input_m");
	for (uint64_t i = 0; i < mix.size(); ++i)
		output.write((char*)&mix[i], sizeof(mix[i]));
	output.close();

	ExtSort("./input_m", "./output_m");

	uint64_t num, val = 0;
	std::ifstream input("./output_m");
	while(input.read((char*)&num, sizeof(num)))
	{
		ASSERT_EQ(num, val);
		val += 1;
	}
	ASSERT_EQ(val, 1000000);
	input.close();

	std::remove("./input_m");
	std::remove("./output_m");
}


int main(int argc, char *argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}