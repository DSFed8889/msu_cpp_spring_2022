#include <iostream>
#include "str_format.hpp"



int main() {
	auto text = str_form::format("{1}+{1} = {0}", 2, "one");
	std::cout << text << std::endl;
}