#include <iostream>
#include <functional>
#include <cstring>
#include <string>
#include "parser.hpp"

namespace token_parser {
    bool TokenParser::IsDigitToken(std::string token) {
        if (!token.length())
            return false;
        for (size_t i = 0; i < token.length(); i++) {
	        if (token[i] < '0' || token[i] > '9')
		        return false;
        }
		try {
			std::stoull(token);
		}
		catch(...) {
			return false;
		}
        return true;
    }

    void TokenParser::SetStartCallback(void_func_t func) {
	    TokenParser::StartCallback = func;
    }

    void TokenParser::SetEndCallback(void_func_t func) {
	    TokenParser::EndCallback = func;
    }

    void TokenParser::SetDigitCallback(uint64_func_t func) {
	    TokenParser::DigitCallback = func;
    }

    void TokenParser::SetStringCallback(str_func_t func) {
	    TokenParser::StringCallback = func;
    }

    void TokenParser::Parse(const std::string & input_str) {
        if (TokenParser::StartCallback)
            StartCallback();
        size_t length = input_str.length();
        for (size_t i = 0; i < length; i++) {
            while (input_str[i] == ' ' || input_str[i] == '\t' || input_str[i] == '\n' || input_str[i] == '\0')
                i++;
            if (i < length) {
                size_t start = i;
                while(i < length && input_str[i] != ' ' && input_str[i] != '\t' && input_str[i] != '\n')
                    i++;
                std::string token = std::string(input_str, start, i-start);
                if (TokenParser::IsDigitToken(token)) {
                    if (TokenParser::DigitCallback)
						TokenParser::DigitCallback(std::stoull(token));
                }
                else if (TokenParser::StringCallback)
                    TokenParser::StringCallback(token);
            }
        }
        if (TokenParser::EndCallback)
            TokenParser::EndCallback();
    }
}