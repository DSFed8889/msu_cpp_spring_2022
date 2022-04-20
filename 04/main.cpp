#include <iostream>
#include "BigInt.hpp"

using namespace big_int;

int main() {
	BigInt a = 1;
	BigInt b("123456789012345678901234567890");
	BigInt c = a * b + 2;
	BigInt d;
	d = std::move(c);
	a = d + b;
	std::cout << a << std::endl;
}