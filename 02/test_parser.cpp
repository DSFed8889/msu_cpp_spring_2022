#include <iostream>
#include <functional>
#include <string>
#include <vector>
#include <typeinfo>
#include <gtest/gtest.h>
#include "parser.hpp"

class TestTokenParser : public ::testing::Test {
public:
	token_parser::TokenParser parser;
	std::vector<std::string> correct_tokens_vector;
	std::vector<std::string> parsed_tokens;
	uint64_t start_func_run_count = 0;
	uint64_t end_func_run_count = 0;
	token_parser::void_func_t start_callback = [this]() {
		TestTokenParser::start_func_run_count++;
	};
	token_parser::void_func_t end_callback = [this]() {
		TestTokenParser::end_func_run_count++;
	};
	token_parser::str_func_t string_callback = [this](std::string new_token) {
		TestTokenParser::parsed_tokens.push_back(new_token);
	};
	token_parser::uint64_func_t digit_callback = [this](uint64_t new_token) {
		TestTokenParser::parsed_tokens.push_back(std::to_string(new_token));
	};
protected:
	void SetUp() {
        std::cout << "SetUp" << std::endl;
	}
	void TearDown() {
		start_func_run_count = 0;
		end_func_run_count = 0;
		correct_tokens_vector.clear();
		parsed_tokens.clear();
        std::cout << "TearDown" << std::endl;
	}
};

TEST_F(TestTokenParser, test_IsDigitToken) {
    std::string test_string = "";
    ASSERT_FALSE(parser.IsDigitToken(test_string));
    for (int i = 0; i < 1000; i++) {
        std::stringstream temp;
        temp << i;
        temp >> test_string;
        ASSERT_TRUE(parser.IsDigitToken(test_string));
    }
    test_string = "452342349234792372934792834789234";
    ASSERT_FALSE(parser.IsDigitToken(test_string));
    test_string = "45234 2312";
    ASSERT_FALSE(parser.IsDigitToken(test_string));
    test_string = " 2312";
    ASSERT_FALSE(parser.IsDigitToken(test_string));
    test_string = "2312 ";
    ASSERT_FALSE(parser.IsDigitToken(test_string));
    test_string = "a123";
    ASSERT_FALSE(parser.IsDigitToken(test_string));
    test_string = "o56445";
    ASSERT_FALSE(parser.IsDigitToken(test_string));
    test_string = "O2312";
    ASSERT_FALSE(parser.IsDigitToken(test_string));
    test_string = "2312q";
    ASSERT_FALSE(parser.IsDigitToken(test_string));
    test_string = "2312Q";
    ASSERT_FALSE(parser.IsDigitToken(test_string));
    test_string = "dsfdq";
    ASSERT_FALSE(parser.IsDigitToken(test_string));
    test_string = "FDJEGR";
    ASSERT_FALSE(parser.IsDigitToken(test_string));
    test_string = "AAAAA";
    ASSERT_FALSE(parser.IsDigitToken(test_string));
    test_string = "aaaaa";
    ASSERT_FALSE(parser.IsDigitToken(test_string));
}

TEST_F(TestTokenParser, test_parse_not_set) {
	//Without tokens
	ASSERT_NO_THROW(parser.Parse(""));
	ASSERT_NO_THROW(parser.Parse("     "));
	ASSERT_NO_THROW(parser.Parse("\t\t\t"));
	ASSERT_NO_THROW(parser.Parse(" \t \t"));
	//Words only
	ASSERT_NO_THROW(parser.Parse("word"));
	ASSERT_NO_THROW(parser.Parse("word word2"));
	ASSERT_NO_THROW(parser.Parse("word word2 "));
	ASSERT_NO_THROW(parser.Parse(" word word2"));
	ASSERT_NO_THROW(parser.Parse("\tword word2\t"));
	ASSERT_NO_THROW(parser.Parse("\tword word2"));
	ASSERT_NO_THROW(parser.Parse("\tword\tword2"));
	ASSERT_NO_THROW(parser.Parse("\t\t\t\tword\t\t\t\tword2\t \t \t\t"));
	//Digits only
	ASSERT_NO_THROW(parser.Parse("123"));
	ASSERT_NO_THROW(parser.Parse("223 32347"));
	ASSERT_NO_THROW(parser.Parse("923 49738 "));
	ASSERT_NO_THROW(parser.Parse(" 133 94547"));
	ASSERT_NO_THROW(parser.Parse("\t5223 82347\t"));
	ASSERT_NO_THROW(parser.Parse("\t523 46247"));
	ASSERT_NO_THROW(parser.Parse("\t323\t322347"));
	ASSERT_NO_THROW(parser.Parse("\t\t\t\t123\t\t\t\t32347\t \t \t\t"));
	//Mixed
	ASSERT_NO_THROW(parser.Parse("word 37626 "));
	ASSERT_NO_THROW(parser.Parse("423435\t\t\t\tword2"));
	ASSERT_NO_THROW(parser.Parse("word 34234"));
	ASSERT_NO_THROW(parser.Parse("word\t\tword2 32343"));
	ASSERT_NO_THROW(parser.Parse("34234 word\t\tword2"));
}

TEST_F(TestTokenParser, test_parse_nullptr) {
	parser.SetStartCallback(nullptr);
	parser.SetEndCallback(nullptr);
	parser.SetDigitCallback(nullptr);
	parser.SetStringCallback(nullptr);
	//Without tokens
	ASSERT_NO_THROW(parser.Parse(""));
	ASSERT_NO_THROW(parser.Parse("     "));
	ASSERT_NO_THROW(parser.Parse("\t\t\t"));
	ASSERT_NO_THROW(parser.Parse(" \t \t"));
	//Words only
	ASSERT_NO_THROW(parser.Parse("word"));
	ASSERT_NO_THROW(parser.Parse("word word2"));
	ASSERT_NO_THROW(parser.Parse("word word2 "));
	ASSERT_NO_THROW(parser.Parse(" word word2"));
	ASSERT_NO_THROW(parser.Parse("\tword word2\t "));
	ASSERT_NO_THROW(parser.Parse("\tword word2"));
	ASSERT_NO_THROW(parser.Parse("\tword\tword2"));
	ASSERT_NO_THROW(parser.Parse("\t\t\t\tword\t\t\t\tword2\t \t \t\t"));
	//Digits only
	ASSERT_NO_THROW(parser.Parse("123"));
	ASSERT_NO_THROW(parser.Parse("223 32347"));
	ASSERT_NO_THROW(parser.Parse("923 49738 "));
	ASSERT_NO_THROW(parser.Parse(" 133 94547"));
	ASSERT_NO_THROW(parser.Parse("\t5223 82347   \t"));
	ASSERT_NO_THROW(parser.Parse("\t523 46247"));
	ASSERT_NO_THROW(parser.Parse("\t323\t322347"));
	ASSERT_NO_THROW(parser.Parse("\t\t\t\t123\t\t\t\t32347\t \t \t\t"));
	//Mixed
	ASSERT_NO_THROW(parser.Parse("word 37626 "));
	ASSERT_NO_THROW(parser.Parse("423435\t\t \t\tword2  "));
	ASSERT_NO_THROW(parser.Parse("word 34234"));
	ASSERT_NO_THROW(parser.Parse("word\t\tword2 32343"));
	ASSERT_NO_THROW(parser.Parse("34234 word\t\tword2"));
}

TEST_F(TestTokenParser, test_parse_without_tokens) {
	parser.SetDigitCallback(digit_callback);
	parser.SetStringCallback(string_callback);
	parser.SetStartCallback(start_callback);
	parser.SetEndCallback(end_callback);
	ASSERT_EQ(start_func_run_count, 0);
	ASSERT_EQ(end_func_run_count, 0);
	//Without tokens
	ASSERT_NO_THROW(parser.Parse(""));
	ASSERT_EQ(correct_tokens_vector, parsed_tokens);
	ASSERT_EQ(start_func_run_count, 1);
	ASSERT_EQ(end_func_run_count, 1);

	ASSERT_NO_THROW(parser.Parse("     "));
	ASSERT_EQ(correct_tokens_vector, parsed_tokens);
	ASSERT_EQ(start_func_run_count, 2);
	ASSERT_EQ(end_func_run_count, 2);

	ASSERT_NO_THROW(parser.Parse("\t\t\t"));
	ASSERT_EQ(correct_tokens_vector, parsed_tokens);
	ASSERT_EQ(start_func_run_count, 3);
	ASSERT_EQ(end_func_run_count, 3);

	ASSERT_NO_THROW(parser.Parse(" \t \t"));
	ASSERT_EQ(correct_tokens_vector, parsed_tokens);
	ASSERT_EQ(start_func_run_count, 4);
	ASSERT_EQ(end_func_run_count, 4);
}

TEST_F(TestTokenParser, test_parse_words_only) {
	parser.SetDigitCallback(digit_callback);
	parser.SetStringCallback(string_callback);
	parser.SetStartCallback(start_callback);
	parser.SetEndCallback(end_callback);
	ASSERT_EQ(start_func_run_count, 0);
	ASSERT_EQ(end_func_run_count, 0);
	//Words only
	ASSERT_NO_THROW(parser.Parse("a"));
	correct_tokens_vector.push_back("a");
	ASSERT_EQ(correct_tokens_vector, parsed_tokens);
	ASSERT_EQ(start_func_run_count, 1);
	ASSERT_EQ(end_func_run_count, 1);

	ASSERT_NO_THROW(parser.Parse("word"));
	correct_tokens_vector.push_back("word");
	ASSERT_EQ(correct_tokens_vector, parsed_tokens);
	ASSERT_EQ(start_func_run_count, 2);
	ASSERT_EQ(end_func_run_count, 2);

	ASSERT_NO_THROW(parser.Parse("word"));
	correct_tokens_vector.push_back("word");
	ASSERT_EQ(correct_tokens_vector, parsed_tokens);
	ASSERT_EQ(start_func_run_count, 3);
	ASSERT_EQ(end_func_run_count, 3);

	ASSERT_NO_THROW(parser.Parse("word2 asdq"));
	correct_tokens_vector.push_back("word2");
	correct_tokens_vector.push_back("asdq");
	ASSERT_EQ(correct_tokens_vector, parsed_tokens);
	ASSERT_EQ(start_func_run_count, 4);
	ASSERT_EQ(end_func_run_count, 4);

	ASSERT_NO_THROW(parser.Parse("42abc qwertyuiop "));
	correct_tokens_vector.push_back("42abc");
	correct_tokens_vector.push_back("qwertyuiop");
	ASSERT_EQ(correct_tokens_vector, parsed_tokens);
	ASSERT_EQ(start_func_run_count, 5);
	ASSERT_EQ(end_func_run_count, 5);

	ASSERT_NO_THROW(parser.Parse(" ssss[] [s]]"));
	correct_tokens_vector.push_back("ssss[]");
	correct_tokens_vector.push_back("[s]]");
	ASSERT_EQ(correct_tokens_vector, parsed_tokens);
	ASSERT_EQ(start_func_run_count, 6);
	ASSERT_EQ(end_func_run_count, 6);

	ASSERT_NO_THROW(parser.Parse("\t\t\t\t./,62\\][\t\tdfhskdf\t\t54hwle2\t \t \t\t"));
	correct_tokens_vector.push_back("./,62\\][");
	correct_tokens_vector.push_back("dfhskdf");
	correct_tokens_vector.push_back("54hwle2");
	ASSERT_EQ(correct_tokens_vector, parsed_tokens);
	ASSERT_EQ(start_func_run_count, 7);
	ASSERT_EQ(end_func_run_count, 7);
}

TEST_F(TestTokenParser, test_parse_digits_only) {
	parser.SetDigitCallback(digit_callback);
	parser.SetStringCallback(string_callback);
	parser.SetStartCallback(start_callback);
	parser.SetEndCallback(end_callback);
	ASSERT_EQ(start_func_run_count, 0);
	ASSERT_EQ(end_func_run_count, 0);
	//Digits only
	ASSERT_NO_THROW(parser.Parse("1"));
	correct_tokens_vector.push_back("1");
	ASSERT_EQ(correct_tokens_vector, parsed_tokens);
	ASSERT_EQ(start_func_run_count, 1);
	ASSERT_EQ(end_func_run_count, 1);

	ASSERT_NO_THROW(parser.Parse("123"));
	correct_tokens_vector.push_back("123");
	ASSERT_EQ(correct_tokens_vector, parsed_tokens);
	ASSERT_EQ(start_func_run_count, 2);
	ASSERT_EQ(end_func_run_count, 2);

	ASSERT_NO_THROW(parser.Parse("223 32347"));
	correct_tokens_vector.push_back("223");
	correct_tokens_vector.push_back("32347");
	ASSERT_EQ(correct_tokens_vector, parsed_tokens);
	ASSERT_EQ(start_func_run_count, 3);
	ASSERT_EQ(end_func_run_count, 3);

	ASSERT_NO_THROW(parser.Parse("923 49738 "));
	correct_tokens_vector.push_back("923");
	correct_tokens_vector.push_back("49738");
	ASSERT_EQ(correct_tokens_vector, parsed_tokens);
	ASSERT_EQ(start_func_run_count, 4);
	ASSERT_EQ(end_func_run_count, 4);

	ASSERT_NO_THROW(parser.Parse(" 133 94547"));
	correct_tokens_vector.push_back("133");
	correct_tokens_vector.push_back("94547");
	ASSERT_EQ(correct_tokens_vector, parsed_tokens);
	ASSERT_EQ(start_func_run_count, 5);
	ASSERT_EQ(end_func_run_count, 5);

	ASSERT_NO_THROW(parser.Parse("\t5223 82347   \t"));
	correct_tokens_vector.push_back("5223");
	correct_tokens_vector.push_back("82347");
	ASSERT_EQ(correct_tokens_vector, parsed_tokens);
	ASSERT_EQ(start_func_run_count, 6);
	ASSERT_EQ(end_func_run_count, 6);

	ASSERT_NO_THROW(parser.Parse("\t523 46247       323"));
	correct_tokens_vector.push_back("523");
	correct_tokens_vector.push_back("46247");
	correct_tokens_vector.push_back("323");
	ASSERT_EQ(correct_tokens_vector, parsed_tokens);
	ASSERT_EQ(start_func_run_count, 7);
	ASSERT_EQ(end_func_run_count, 7);

	ASSERT_NO_THROW(parser.Parse("\t323\t322347"));
	correct_tokens_vector.push_back("323");
	correct_tokens_vector.push_back("322347");
	ASSERT_EQ(correct_tokens_vector, parsed_tokens);
	ASSERT_EQ(start_func_run_count, 8);
	ASSERT_EQ(end_func_run_count, 8);

	ASSERT_NO_THROW(parser.Parse("\t\t\t\t123\t\t\t\t32347\t \t \t\t"));
	correct_tokens_vector.push_back("123");
	correct_tokens_vector.push_back("32347");
	ASSERT_EQ(correct_tokens_vector, parsed_tokens);
	ASSERT_EQ(start_func_run_count, 9);
	ASSERT_EQ(end_func_run_count, 9);
}

TEST_F(TestTokenParser, test_parse_mixed) {
	parser.SetDigitCallback(digit_callback);
	parser.SetStringCallback(string_callback);
	parser.SetStartCallback(start_callback);
	parser.SetEndCallback(end_callback);
	ASSERT_EQ(start_func_run_count, 0);
	ASSERT_EQ(end_func_run_count, 0);
	//Mixed
	ASSERT_NO_THROW(parser.Parse("word 37626 "));
	correct_tokens_vector.push_back("word");
	correct_tokens_vector.push_back("37626");
	ASSERT_EQ(correct_tokens_vector, parsed_tokens);
	ASSERT_EQ(start_func_run_count, 1);
	ASSERT_EQ(end_func_run_count, 1);

	ASSERT_NO_THROW(parser.Parse("423435\t\t \t\tword2  "));
	correct_tokens_vector.push_back("423435");
	correct_tokens_vector.push_back("word2");
	ASSERT_EQ(correct_tokens_vector, parsed_tokens);
	ASSERT_EQ(start_func_run_count, 2);
	ASSERT_EQ(end_func_run_count, 2);

	ASSERT_NO_THROW(parser.Parse("word 34234"));
	correct_tokens_vector.push_back("word");
	correct_tokens_vector.push_back("34234");
	ASSERT_EQ(correct_tokens_vector, parsed_tokens);
	ASSERT_EQ(start_func_run_count, 3);
	ASSERT_EQ(end_func_run_count, 3);

	ASSERT_NO_THROW(parser.Parse("word\t\tword2 32343"));
	correct_tokens_vector.push_back("word");
	correct_tokens_vector.push_back("word2");
	correct_tokens_vector.push_back("32343");
	ASSERT_EQ(correct_tokens_vector, parsed_tokens);
	ASSERT_EQ(start_func_run_count, 4);
	ASSERT_EQ(end_func_run_count, 4);

	ASSERT_NO_THROW(parser.Parse("34234 word\t\tword2"));
	correct_tokens_vector.push_back("34234");
	correct_tokens_vector.push_back("word");
	correct_tokens_vector.push_back("word2");
	ASSERT_EQ(correct_tokens_vector, parsed_tokens);
	ASSERT_EQ(start_func_run_count, 5);
	ASSERT_EQ(end_func_run_count, 5);
}

TEST_F(TestTokenParser, test_reset_callback) {
	//Callback reset test
	parser.SetDigitCallback(digit_callback);
	parser.SetStringCallback(string_callback);
	parser.SetStartCallback(start_callback);
	parser.SetEndCallback(end_callback);
	ASSERT_EQ(start_func_run_count, 0);
	ASSERT_EQ(end_func_run_count, 0);

	ASSERT_NO_THROW(parser.Parse("word 37626 "));
	correct_tokens_vector.push_back("word");
	correct_tokens_vector.push_back("37626");
	ASSERT_EQ(correct_tokens_vector, parsed_tokens);
	ASSERT_EQ(start_func_run_count, 1);
	ASSERT_EQ(end_func_run_count, 1);

	//Setting nullptr
	parser.SetDigitCallback(nullptr);
	parser.SetStringCallback(nullptr);
	parser.SetStartCallback(nullptr);
	parser.SetEndCallback(nullptr);

	ASSERT_NO_THROW(parser.Parse("423435\t\t \t\tword2  "));
	ASSERT_EQ(correct_tokens_vector, parsed_tokens);
	ASSERT_EQ(start_func_run_count, 1);
	ASSERT_EQ(end_func_run_count, 1);

	//Resetting back
	parser.SetDigitCallback(digit_callback);
	parser.SetStringCallback(string_callback);
	parser.SetStartCallback(start_callback);
	parser.SetEndCallback(end_callback);

	ASSERT_NO_THROW(parser.Parse("423435\t\t \t\tword2  "));
	correct_tokens_vector.push_back("423435");
	correct_tokens_vector.push_back("word2");
	ASSERT_EQ(correct_tokens_vector, parsed_tokens);
	ASSERT_EQ(start_func_run_count, 2);
	ASSERT_EQ(end_func_run_count, 2);
}

TEST_F(TestTokenParser, test_parse_big_digits) {
	std::vector<uint64_t> digit_vector;
	std::vector<uint64_t> correct_digit_vector;
	token_parser::uint64_func_t digit_handler = [&digit_vector](uint64_t digit) {
		digit_vector.push_back(digit);
	};
	parser.SetDigitCallback(digit_handler);
	parser.SetStringCallback(string_callback);

	parser.Parse("0 1 10 18446744073709551615 18446744073709551616 36893488147419103232");
	parser.Parse("000000000000000000000000000000000000000000000000000000000000000000008");
	correct_digit_vector.push_back(0);
	correct_digit_vector.push_back(1);
	correct_digit_vector.push_back(10);
	correct_digit_vector.push_back(18446744073709551615ULL);
	correct_digit_vector.push_back(8);
	correct_tokens_vector.push_back("18446744073709551616");
	correct_tokens_vector.push_back("36893488147419103232");
	//В parsed_tokens вставляет строчки только string_callback
	ASSERT_EQ(correct_digit_vector, digit_vector);
	ASSERT_EQ(correct_tokens_vector, parsed_tokens);
}

int main(int argc, char *argv[]) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}