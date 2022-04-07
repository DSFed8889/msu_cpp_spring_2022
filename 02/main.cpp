#include <iostream>
#include <string>
#include "parser.hpp"

size_t count = 0, sum = 0;

void my_string_parser(std::string token) {
    count += token.length();
}

void my_digit_parser(std::string token) {
    sum += std::stoi(token);
}

void start_func(void) {
    std::cout << "Parsing starts!" << std::endl;
}

void end_func(void) {
    std::cout << "Parsing ended! Line config: strings_sum_len=" << count << " digits_sum=" << sum << std::endl;
}

int main() {
    token_parser::TokenParser parser;
    std::string line;
    parser.SetStartCallback(start_func);
    parser.SetEndCallback(end_func);
    parser.SetDigitCallback(my_digit_parser);
    parser.SetStringCallback(my_string_parser);
    while (std::getline(std::cin, line)) {
        parser.Parse(line);
    }
}