#include <iostream>
#include <functional>
#include <string>
#include <gtest/gtest.h>
#include "parser.hpp"

class TestTokenParser : public ::testing::Test {
protected:
	token_parser::TokenParser parser1, parser2, parser3, parser4;
	void SetUp() {
        std::cout << "SetUp" << std::endl;
		std::cout.rdbuf(nullptr);
	}
	void TearDown() {
        std::cout << "TearDown" << std::endl;
	}
};

size_t sum = 0, start_count = 0, end_count = 0;
std::string max_len_token = "";

void empty_func() {
}

void empty_func_for_token_callback(std::string) {
}

void my_string_parser(std::string token) {
    if (token.length() > max_len_token.length())
        max_len_token = token;
}

void my_digit_parser(std::string token) {
    sum += std::stoi(token);
}

void start_func(void) {
    start_count++;
    std::cout << "Parsing starts!" << std::endl;
}

void end_func(void) {
    end_count++;
    std::cout << "Parsing ended! Line config: max_len_string=" << max_len_token << " digits_sum=" << sum << std::endl;
}

TEST_F(TestTokenParser, test_IsDigitToken) {
    std::string test_string = "";
    ASSERT_FALSE(parser1.IsDigitToken(test_string));
    for (int i = 0; i < 1000; i++) {
        std::stringstream temp;
        temp << i;
        temp >> test_string;
        ASSERT_TRUE(parser1.IsDigitToken(test_string));
    }
    test_string = "452342349234792372934792834789234";
    ASSERT_TRUE(parser1.IsDigitToken(test_string));
    test_string = "45234 2312";
    ASSERT_FALSE(parser1.IsDigitToken(test_string));
    test_string = " 2312";
    ASSERT_FALSE(parser1.IsDigitToken(test_string));
    test_string = "2312 ";
    ASSERT_FALSE(parser1.IsDigitToken(test_string));
    test_string = "a123";
    ASSERT_FALSE(parser1.IsDigitToken(test_string));
    test_string = "o56445";
    ASSERT_FALSE(parser1.IsDigitToken(test_string));
    test_string = "O2312";
    ASSERT_FALSE(parser1.IsDigitToken(test_string));
    test_string = "2312q";
    ASSERT_FALSE(parser1.IsDigitToken(test_string));
    test_string = "2312Q";
    ASSERT_FALSE(parser1.IsDigitToken(test_string));
    test_string = "dsfdq";
    ASSERT_FALSE(parser1.IsDigitToken(test_string));
    test_string = "FDJEGR";
    ASSERT_FALSE(parser1.IsDigitToken(test_string));
    test_string = "AAAAA";
    ASSERT_FALSE(parser1.IsDigitToken(test_string));
    test_string = "aaaaa";
    ASSERT_FALSE(parser1.IsDigitToken(test_string));
}

TEST_F(TestTokenParser, test_parse1) {
	start_count = 0;
	end_count = 0;
	sum = 0;
	max_len_token = "";
	// Test of parsing without callback-functions
    std::string test_string = "";
    parser2.Parse(test_string);
	// parsing empty string
    ASSERT_EQ(start_count, 0);
    ASSERT_EQ(end_count, 0);
    ASSERT_EQ(max_len_token.compare(""), 0);
    ASSERT_EQ(sum, 0);
	// parsing  not empty strings
    test_string = "sdfsf dfwf 4234 234dfw s";
	parser2.Parse(test_string);
	
    ASSERT_EQ(start_count, 0);
    ASSERT_EQ(end_count, 0);
    ASSERT_EQ(max_len_token.compare(""), 0);
    ASSERT_EQ(sum, 0);
	
	test_string = "                d";
	parser2.Parse(test_string);
	
	ASSERT_EQ(start_count, 0);
	ASSERT_EQ(end_count, 0);
	ASSERT_EQ(max_len_token.compare(""), 0);
	ASSERT_EQ(sum, 0);

	test_string = "s                   ";
	parser2.Parse(test_string);
	
	ASSERT_EQ(start_count, 0);
	ASSERT_EQ(end_count, 0);
	ASSERT_EQ(max_len_token.compare(""), 0);
	ASSERT_EQ(sum, 0);

	test_string = "                5";
	parser2.Parse(test_string);
	
	ASSERT_EQ(start_count, 0);
	ASSERT_EQ(end_count, 0);
	ASSERT_EQ(max_len_token.compare(""), 0);
	ASSERT_EQ(sum, 0);
	
	test_string = "4                   ";
	parser2.Parse(test_string);
	
	ASSERT_EQ(start_count, 0);
	ASSERT_EQ(end_count, 0);
	ASSERT_EQ(max_len_token.compare(""), 0);
	ASSERT_EQ(sum, 0);
	
	test_string = "\t\t\t\t\t\t\t5";
	parser2.Parse(test_string);
	
	ASSERT_EQ(start_count, 0);
	ASSERT_EQ(end_count, 0);
	ASSERT_EQ(max_len_token.compare(""), 0);
	ASSERT_EQ(sum, 0);
	
	test_string = "    \t\t\t\t4\t\t     \t\t4434t\t\t\t    \t";
	parser2.Parse(test_string);
	
	ASSERT_EQ(start_count, 0);
	ASSERT_EQ(end_count, 0);
	ASSERT_EQ(max_len_token.compare(""), 0);
	ASSERT_EQ(sum, 0);
}

TEST_F(TestTokenParser, test_parse2) {
	start_count = 0;
	end_count = 0;
	sum = 0;
	max_len_token = "";
	// Test of parsing with callback-functions
	std::string test_string = "";
	parser3.SetStartCallback(start_func);
	parser3.SetEndCallback(end_func);
	parser3.SetStringCallback(my_string_parser);
	parser3.SetDigitCallback(my_digit_parser);
	parser3.Parse(test_string);
	// parsing empty string
	ASSERT_EQ(start_count, 1);
	ASSERT_EQ(end_count, 1);
	ASSERT_EQ(max_len_token.compare(""), 0);
	ASSERT_EQ(sum, 0);

    test_string = "\t\t\t";
	parser3.Parse(test_string);
	
	ASSERT_EQ(start_count, 2);
	ASSERT_EQ(end_count, 2);
	ASSERT_EQ(max_len_token.compare(""), 0);
	ASSERT_EQ(sum, 0);
	
	test_string = "   ";
	parser3.Parse(test_string);
	
	ASSERT_EQ(start_count, 3);
	ASSERT_EQ(end_count, 3);
	ASSERT_EQ(max_len_token.compare(""), 0);
	ASSERT_EQ(sum, 0);
	
	test_string = "\t\t\0  \t  \t";
	parser3.Parse(test_string);
	
	ASSERT_EQ(start_count, 4);
	ASSERT_EQ(end_count, 4);
	ASSERT_EQ(max_len_token.compare(""), 0);
	ASSERT_EQ(sum, 0);
	// parsing  not empty strings
	test_string = "sdfsf dfwf 4234 234dfw s";
	parser3.Parse(test_string);
	
	ASSERT_EQ(start_count, 5);
	ASSERT_EQ(end_count, 5);
	ASSERT_EQ(max_len_token.compare("234dfw"), 0);
	ASSERT_EQ(sum, 4234);
	
	test_string = "                d";
	max_len_token = "";
	parser3.Parse(test_string);
	
	ASSERT_EQ(start_count, 6);
	ASSERT_EQ(end_count, 6);
	ASSERT_EQ(max_len_token.compare("d"), 0);
	ASSERT_EQ(sum, 4234);
	
	test_string = "s                   ";
	max_len_token = "";
	sum = 0;
	parser3.Parse(test_string);
	
	ASSERT_EQ(start_count, 7);
	ASSERT_EQ(end_count, 7);
	ASSERT_EQ(max_len_token.compare("s"), 0);
	ASSERT_EQ(sum, 0);
	
	test_string = "                5";
	max_len_token = "";
	sum = 0;
	parser3.Parse(test_string);
	
	ASSERT_EQ(start_count, 8);
	ASSERT_EQ(end_count, 8);
	ASSERT_EQ(max_len_token.compare(""), 0);
	ASSERT_EQ(sum, 5);
	
	test_string = "4                   ";
	parser3.Parse(test_string);
	
	ASSERT_EQ(start_count, 9);
	ASSERT_EQ(end_count, 9);
	ASSERT_EQ(max_len_token.compare(""), 0);
	ASSERT_EQ(sum, 9);
	
	test_string = "\t\t\t\t\t\t\t5";
	parser3.Parse(test_string);
	
	ASSERT_EQ(start_count, 10);
	ASSERT_EQ(end_count, 10);
	ASSERT_EQ(max_len_token.compare(""), 0);
	ASSERT_EQ(sum, 14);
	
	test_string = "    \t\t\t\t4\t\t     \t\t4434t\t\t\t    \t";
	parser3.Parse(test_string);
	
	ASSERT_EQ(start_count, 11);
	ASSERT_EQ(end_count, 11);
	ASSERT_EQ(max_len_token.compare("4434t"), 0);
	ASSERT_EQ(sum, 18);
}

TEST_F(TestTokenParser, test_parse3) {
	start_count = 0;
	end_count = 0;
	sum = 0;
	max_len_token = "";
	//Testing work of Callback setters
	parser4.SetStartCallback(start_func);
	std::string test_string = "sdfsf dfwf 4234 234dfw s";
	parser4.Parse(test_string);
	
	ASSERT_EQ(start_count, 1);
	ASSERT_EQ(end_count, 0);
	ASSERT_EQ(max_len_token.compare(""), 0);
	ASSERT_EQ(sum, 0);
	
	parser4.SetEndCallback(end_func);
	test_string = "sdfsf dfwf 4234 234dfw s";
	parser4.Parse(test_string);
	
	ASSERT_EQ(start_count, 2);
	ASSERT_EQ(end_count, 1);
	ASSERT_EQ(max_len_token.compare(""), 0);
	ASSERT_EQ(sum, 0);
	
	parser4.SetStringCallback(my_string_parser);
	test_string = "sdfsf dfwf 4234 234dfw s";
	parser4.Parse(test_string);
	
	ASSERT_EQ(start_count, 3);
	ASSERT_EQ(end_count, 2);
	ASSERT_EQ(max_len_token.compare("234dfw"), 0);
	ASSERT_EQ(sum, 0);
	
	parser4.SetDigitCallback(my_digit_parser);
	test_string = "dsdfkd 3 2 3 dkf 87 dk";
	parser4.Parse(test_string);
	
	ASSERT_EQ(start_count, 4);
	ASSERT_EQ(end_count, 3);
	ASSERT_EQ(max_len_token.compare("234dfw"), 0);
	ASSERT_EQ(sum, 95);
	//parser Callback-functions resetting
	parser4.SetStartCallback(end_func);
	test_string = "dsdfkd 3 2 3 dkf 87 dk";
	start_count = 0;
	end_count = 0;
	parser4.Parse(test_string);
	
	ASSERT_EQ(start_count, 0);
	ASSERT_EQ(end_count, 2);
	ASSERT_EQ(max_len_token.compare("234dfw"), 0);
	ASSERT_EQ(sum, 190);

	parser4.SetDigitCallback(my_string_parser);
	parser4.SetStringCallback(empty_func_for_token_callback);
	test_string = "dsdfkd 3 2 3 dkf 87 dk";
	max_len_token = "";
	parser4.Parse(test_string);
	
	ASSERT_EQ(start_count, 0);
	ASSERT_EQ(end_count, 4);
	ASSERT_EQ(max_len_token.compare("87"), 0);
	ASSERT_EQ(sum, 190);

	parser4.SetEndCallback(start_func);
	parser4.SetStartCallback(empty_func);
	test_string = "dsdfkd 3 2 3 dkf 87 dk";
	start_count = 0;
	end_count = 0;
	parser4.Parse(test_string);
	
	ASSERT_EQ(start_count, 1);
	ASSERT_EQ(end_count, 0);
	ASSERT_EQ(max_len_token.compare("87"), 0);
	ASSERT_EQ(sum, 190);
}

int main(int argc, char *argv[]) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}