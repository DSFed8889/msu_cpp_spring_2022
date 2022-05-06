#pragma once

#include <string>
#include <sstream>
#include <stdexcept>

namespace str_form {
	class BracesException: public std::exception {
		const char* description;
	public:
		BracesException(const char* des = "Braces error!") {
			description = des;
		}
		const char * what() const throw() override{
			return description;
		}
	};
	
	class ArgumentException: public std::exception {
		const char* description;
	public:
		ArgumentException(const char* des = "Arguments error!") {
			description = des;
		}
		const char * what() const throw() override{
			return description;
		}
	};
	
	template<typename T>
	struct StreamPushable
	{
	private:
		static std::ostream test_stream;
		struct FakeType {};
	public:
		using ExpectedType = decltype(test_stream << 0);
		static constexpr bool value = std::is_same<ExpectedType, decltype(StreamPushable<T>::check((T*)nullptr))>::value;

		static FakeType check(...);

		template<typename U>
		static auto check(U *u) -> decltype(test_stream << (*u));
	};
	
	template<class T>
	std::string any_to_s(T i) {
		std::stringstream s;
		if constexpr (StreamPushable<T>::value)
			s << i;
		else
			throw ArgumentException("Arguments must be streamable!");
		return s.str();
	}
	
	void push_into_string(std::string&, size_t&) {}
	
	template <class Head, class... Tail>
	void push_into_string(std::string& str, size_t& num, Head& head, const Tail&... tail) {
		std::string s("{");
		s += any_to_s(num);
		s += std::string("}");
		size_t found;
		while ((found = str.find(s, 0)) != std::string::npos)
			str.replace(found, s.length(), std::string(any_to_s(head)));
		num++;
		push_into_string(str, num, tail...);
	}
	
	void check_braces_in_braces(std::string& str) {
		size_t start = 0, open_id, close_id = -1;
		while ((open_id = str.find("{", start)) != std::string::npos) {
			if ((close_id = str.find("}", open_id)) == std::string::npos)
				throw BracesException("Wrong braces sequance!");
			if (close_id == open_id + 1)
				throw BracesException("Empty braces!");
			if (str.find("{", open_id + 1) != std::string::npos && str.find("{", open_id + 1) < close_id)
				throw BracesException("Wrong braces sequance!");
			try {
				std::stoi(str.substr(open_id + 1, close_id));
			}
			catch (const std::exception& e) {
				throw BracesException("Not number in braces!");
			}
			start = close_id;
		}
		if (str.find('}', close_id + 1) != std::string::npos)
			throw BracesException("Wrong braces sequance!");
	}
	
	template <class InStr, class... Args>
	std::string format(const InStr c_str, const Args&... args) {
		std::string str(c_str);
		size_t num = 0;
		check_braces_in_braces(str);
		push_into_string(str, num, args...);
		if (str.find('{', 0) != std::string::npos || str.find('}', 0) != std::string::npos)
			throw ArgumentException("Too few arguments!");
		return str;
	}
}