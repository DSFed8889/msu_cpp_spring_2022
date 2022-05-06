#include <gtest/gtest.h>
#include <sstream>
#include <vector>
#include "str_format.hpp"

using namespace str_form;


class TestFormat : public ::testing::Test {
public:
protected:
	void SetUp() {
		std::cout << "SetUp" << std::endl;
	}
	void TearDown() {
		std::cout << "TearDown" << std::endl;
	}
};

TEST_F(TestFormat, test_without_args) {
	ASSERT_NO_THROW(format("String without any changes"));
	ASSERT_NO_THROW(format("String without any changes", 1));
	ASSERT_NO_THROW(format("String without any changes", 2));
	ASSERT_NO_THROW(format("String without any changes", true));
	ASSERT_NO_THROW(format("String without any changes", false));
	ASSERT_NO_THROW(format("String without any changes", "str"));
	ASSERT_NO_THROW(format("String without any changes", 1, "str"));
	ASSERT_NO_THROW(format("String without any changes", 0, 0));
	ASSERT_NO_THROW(format("String without any changes", 1, 1));
	ASSERT_NO_THROW(format("String without any changes", 0, false));
	ASSERT_NO_THROW(format("String without any changes", 1, false));
	ASSERT_NO_THROW(format("String without any changes", 150, false));
	ASSERT_NO_THROW(format("String without any changes", 4, "str"));
	ASSERT_NO_THROW(format("String without any changes", false, 0));
	ASSERT_NO_THROW(format("String without any changes", true, 2000));
	ASSERT_NO_THROW(format("String without any changes", "true", 2000));
	ASSERT_NO_THROW(format("String without any changes", "true", 2000, 892));
	ASSERT_NO_THROW(format("String without any changes", true, 2000, "false", 90, 203, "any_str"));
}

TEST_F(TestFormat, test_errors) {
	bool error_catched = false;
	
	try {
		format("{");
	}
	catch (const BracesException& e) {
		error_catched = true;
		ASSERT_EQ(e.what(), "Wrong braces sequance!");
	}
	ASSERT_TRUE(error_catched);
	error_catched = false;

	try {
		format("}");
	}
	catch (const BracesException& e) {
		error_catched = true;
	ASSERT_EQ(e.what(), "Wrong braces sequance!");
	}
	ASSERT_TRUE(error_catched);
	error_catched = false;

	try {
		format("{}");
	}
	catch (const BracesException& e) {
		error_catched = true;
	ASSERT_EQ(e.what(), "Empty braces!");
	}
	ASSERT_TRUE(error_catched);
	error_catched = false;

	try {
		format("{wdf}", 0);
	}
	catch (const BracesException& e) {
		error_catched = true;
	ASSERT_EQ(e.what(), "Not number in braces!");
	}
	ASSERT_TRUE(error_catched);
	error_catched = false;

	try {
		format("sdfdf{w}");
	}
	catch (const BracesException& e) {
		error_catched = true;
		ASSERT_EQ(e.what(), "Not number in braces!");
	}

	try {
		format("sdfdf    {w}     ", 1, 2, 3);
	}
	catch (const BracesException& e) {
		error_catched = true;
		ASSERT_EQ(e.what(), "Not number in braces!");
	}
	ASSERT_TRUE(error_catched);
	error_catched = false;

	try {
		format("str{{0}}", "sdt");
	}
	catch (const BracesException& e) {
		error_catched = true;
		ASSERT_EQ(e.what(), "Wrong braces sequance!");
	}
	ASSERT_TRUE(error_catched);
	error_catched = false;

	try {
		format("str{{0}}", 1, "str");
	}
	catch (const BracesException& e) {
		error_catched = true;
		ASSERT_EQ(e.what(), "Wrong braces sequance!");
	}
	ASSERT_TRUE(error_catched);
	error_catched = false;

	try {
		format("str{sdasd{0} asd}", 0);
	}
	catch (const BracesException& e) {
		error_catched = true;
		ASSERT_EQ(e.what(), "Wrong braces sequance!");
	}
	ASSERT_TRUE(error_catched);
	error_catched = false;

	try {
		format("str{0} {1}{2}");
	}
	catch (const ArgumentException& e) {
		error_catched = true;
		ASSERT_EQ(e.what(), "Too few arguments!");
	}
	ASSERT_TRUE(error_catched);
	error_catched = false;

	try {
		format("str{0} {1}{2}", 0);
	}
	catch (const ArgumentException& e) {
		error_catched = true;
		ASSERT_EQ(e.what(), "Too few arguments!");
	}
	ASSERT_TRUE(error_catched);
	error_catched = false;

	try {
		format("str{0} {1}{2}", 0, 1);
	}
	catch (const ArgumentException& e) {
		error_catched = true;
		ASSERT_EQ(e.what(), "Too few arguments!");
	}
	ASSERT_TRUE(error_catched);
	error_catched = false;

	try {
		format("str{0} {1}{2} {3}", 0, 1, 2);
	}
	catch (const ArgumentException& e) {
		error_catched = true;
		ASSERT_EQ(e.what(), "Too few arguments!");
	}
	ASSERT_TRUE(error_catched);
	error_catched = false;

	try {
		format("str{0} {1}{2} {3}", 0, 1, 2);
	}
	catch (const ArgumentException& e) {
		error_catched = true;
		ASSERT_EQ(e.what(), "Too few arguments!");
	}
	ASSERT_TRUE(error_catched);
	error_catched = false;

	std::vector<int> a;
	a.push_back(9);
	try {
		format("str{0} {1}{2} {3}", 0, 1, 2, a);
	}
	catch (const ArgumentException& e) {
		error_catched = true;
		ASSERT_EQ(e.what(), "Arguments must be streamable!");
	}
	ASSERT_TRUE(error_catched);
	error_catched = false;
}

TEST_F(TestFormat, test_what_return) {
	ASSERT_EQ(format("str without changes"), "str without changes");
	ASSERT_EQ(format("str without changes", 0), "str without changes");
	ASSERT_EQ(format("str without changes", 170), "str without changes");
	ASSERT_EQ(format("str without changes", true), "str without changes");
	ASSERT_EQ(format("str without changes", "add"), "str without changes");
	ASSERT_EQ(format("str without changes", "add", 1), "str without changes");
	ASSERT_EQ(format("str without changes", "add", "add2", "add3"), "str without changes");
	ASSERT_EQ(format("{1}+{1} = {0}", 4, std::string("2")), "2+2 = 4");
	ASSERT_EQ(format("{1}+{1} = {0}", 4, std::string("2"), true, false), "2+2 = 4");
	ASSERT_EQ(format("{1}+{1} = {0}", false, true), "1+1 = 0");
}


int main(int argc, char *argv[]) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}