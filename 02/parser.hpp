#pragma once

#include <iostream>
#include <functional>
#include <string>


namespace token_parser {
	using void_func_t = std::function <void()>;
	using uint64_func_t = std::function <void(uint64_t)>;
	using str_func_t = std::function <void(std::string)>;

	class TokenParser {
	    void_func_t StartCallback;
	    void_func_t EndCallback;
	    str_func_t StringCallback;
        uint64_func_t DigitCallback;
    public:
        TokenParser() = default;

        bool IsDigitToken(std::string);

        // Устанавливаем callback-функцию перед стартом парсинга.
        void SetStartCallback(void_func_t);

        // Устанавливаем callback-функцию после окончания парсинга.
        void SetEndCallback(void_func_t);

        // Устанавливаем callback-функцию для обработки чисел.
        void SetDigitCallback(uint64_func_t);

        // Устанавливаем callback-функцию для обработки строк-токенов.
        void SetStringCallback(str_func_t);

        void Parse(const std::string &);
    };
}