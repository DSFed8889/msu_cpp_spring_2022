#pragma once

#include <iostream>
#include <functional>
#include <string>

namespace token_parser {
    class TokenParser {
        std::function <void()> StartCallback;
        std::function <void()> EndCallback;
        std::function <void(std::string)> StringCallback;
        std::function <void(std::string)> DigitCallback;
    public:
        TokenParser() = default;

        bool IsDigitToken(std::string);

        // Устанавливаем callback-функцию перед стартом парсинга.
        void SetStartCallback(std::function <void()>);

        // Устанавливаем callback-функцию после окончания парсинга.
        void SetEndCallback(std::function <void()>);

        // Устанавливаем callback-функцию для обработки чисел.
        void SetDigitCallback(std::function <void(std::string)>);

        // Устанавливаем callback-функцию для обработки строк-токенов.
        void SetStringCallback(std::function <void(std::string)>);

        void Parse(const std::string &);
    };
}