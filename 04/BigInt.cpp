#include "BigInt.hpp"
#include <cmath>

using namespace big_int;

BigInt::BigInt(int32_t num) {
	sign = '+';
	if (num < 0) {
		sign = '-';
		num *= -1;
	}
	size = 1;
	int32_t temp = num;
	while ((temp /= 10) != 0)
		++size;
	data = new char[size];
	data[0] = 0;
	for (size_t i = 0; i < size; i++) {
		data[i] = num % 10;
		num /= 10;
	}
}

BigInt::BigInt(std::string str) {
	if (str.length() != 0) {
		sign = '+';
		if (str[0] == '-' || str[0] == '+') {
			sign = str[0];
			str = str.substr(1, str.length());
		}
		if (str.length() == 0)
			throw std::invalid_argument("Warning! Numbers count have to be > 0!");
		while (str[0] == 0 && str.length() > 1)
			str = str.substr(1, str.length());
		if (str.length() == 1 && str[0] == '0')
			sign = '+';
		size = str.length();
		data = new char[size];
		for (size_t i = 0; i < size; i++) {
			if (str[i] - '0' > 9 || str[i] - '0' < 0)
				throw std::invalid_argument("Wrong string!");
			data[size - i - 1] = str[i] - '0';
		}
	}
	else
		throw std::invalid_argument("Warning! String length have to be > 0!");
}

BigInt::BigInt(const BigInt &num) {
	sign = num.sign;
	size = num.size;
	data = new char[size];
	for (size_t i = 0; i < size; i++)
		data[i] = num.data[i];
}

BigInt::BigInt(BigInt &&num) {
	sign = num.sign;
	size = num.size;
	delete[] data;
	data = num.data;
	num.data = nullptr;
	num.size = 0;
	num.sign = '+';
}

BigInt::~BigInt() {
	delete[] data;
}

BigInt &BigInt::operator=(const BigInt &num) {
	if (this == &num)
		return *this;
	sign = num.sign;
	size = num.size;
	data = new char[size];
	for (size_t i = 0; i < size; i++)
		data[i] = num.data[i];
	return *this;
}

BigInt &BigInt::operator=(BigInt &&num) {
	if (this == &num)
		return *this;
	sign = num.sign;
	size = num.size;
	delete[] data;
	data = num.data;
	num.data = nullptr;
	num.size = 0;
	num.sign = '+';
	return *this;
}

BigInt BigInt::operator+(const BigInt &num) const{
	if (num.sign == sign) {
		if (sign == '+') {
			if (num > (*this))
				return num + (*this);
		}
		else {
			if ((-num) > (-(*this)))
				return num + (*this);
		}
		BigInt result;
		result.sign = sign;
		result.size = size + 1;
		delete[] result.data;
		result.data = new char[result.size];
		for (size_t i = 0; i < size; i++)
			result.data[i] = data[i];
		result.data[size] = 0;
		char temp_digit = 0;
		for (size_t i = 0; i < num.size; i++) {
			result.data[i] = result.data[i] + num.data[i] + temp_digit;
			temp_digit = result.data[i] / 10;
			result.data[i] %= 10;
		}
		for (size_t i = num.size; i < result.size; i++) {
			result.data[i] = result.data[i] + temp_digit;
			temp_digit = result.data[i] / 10;
			result.data[i] %= 10;
		}
		while (result.data[result.size - 1] == 0 && result.size > 1)
			result.size--;
		return result;
	}
	else if (sign == '-')
		return num - (-(*this));
	else
		return (*this) - (-num);
}

BigInt BigInt::operator+(const int32_t &num) const{
	return (*this) + BigInt(num);
}

//BigInt operator+(const int32_t &num1, const BigInt &num2) {
//	return BigInt(num1) + num2;
//}

BigInt BigInt::operator-(const BigInt &num) const{
	if (sign == num.sign) {
		if (sign == '-')
			return (-num) - (-(*this));
		if (num > (*this))
			return -(num - (*this));
		BigInt result = (*this);
		int temp_num = 0;
		for (size_t i = 0; i < num.size; i++) {
			int temp = result.data[i] - num.data[i] - temp_num;
			if (temp < 0) {
				result.data[i] = 10 + temp;
				temp_num = 1;
			}
			else {
				result.data[i] = temp;
				temp_num = 0;
			}
		}
		for (size_t i = num.size; i < result.size; i++) {
			int temp = result.data[i] - temp_num;
			if (temp < 0) {
				result.data[i] = 10 + temp;
				temp_num = 1;
			}
			else {
				result.data[i] = temp;
				temp_num = 0;
			}
		}
		while (result.data[result.size - 1] == 0 && result.size > 1)
			--result.size;
		return result;
	}
	if (sign == '-')
		return (*this) + (-num);
	return (*this) + (-num);
}

BigInt BigInt::operator-(const int32_t &num) const{
	return (*this) - BigInt(num);
}

bool BigInt::operator>(const BigInt &num) const{
	if (sign == num.sign) {
		if (sign == '+') {
			if (size > num.size)
				return true;
			if (size == num.size) {
				for (size_t i = 0; i < size; i++) {
					if (data[size - 1 - i] > num.data[size - 1 - i])
						return true;
					if (data[size - 1 - i] < num.data[size - 1 - i])
						return false;
				}
				return false;
			}
			return false;
		}
		else
			return (-(*this)) < (-num);
	}
	else if (sign == '+')
		return true;
	return false;
}

bool BigInt::operator==(const BigInt &num) const {
	if (size == num.size) {
		if (sign == num.sign) {
			for (size_t i = 0; i < size; i++)
				if (data[i] != num.data[i])
					return false;
			return true;
		}
		return false;
	}
	return false;
}

bool BigInt::operator!=(const BigInt &num) const {
	return !((*this) == num);
}

bool BigInt::operator>=(const BigInt &num) const {
	return ((*this) > num || (*this) == num);
}

bool BigInt::operator<(const BigInt &num) const {
	std::cout << (*this) << ' ' << num << std::endl;
	return !((*this) >= num );
}

bool BigInt::operator<=(const BigInt &num) const {
	return (*this) == num || (*this) < num;
}

BigInt BigInt::operator-() const{
	BigInt result = (*this);
	result.sign = '-';
	if (sign == '-')
		result.sign = '+';
	return result;
}

//BigInt operator-(const int32_t &num1, const BigInt &num2) {
//	return BigInt(num1) - num2;
//}

BigInt BigInt::operator*(const BigInt &num) const{
	BigInt result;
	for (size_t i = 0; i < num.size; i++) {
		BigInt temp_num;
		delete[] temp_num.data;
		temp_num.size = size + i;
		temp_num.data = new char[temp_num.size];
		for (size_t j = 0; j < temp_num.size; j++)
			temp_num.data[j] = 0;
		int temp = 0;
		for (size_t j = 0; j < size; j++) {
			temp_num.data[j + i] = (data[j] * num.data[i] + temp) % 10;
			temp = (data[j] * num.data[i] + temp) / 10;
		}
		while (temp_num.data[temp_num.size - 1] == 0 && temp_num.size > 1)
			--temp_num.size;
		result = result + temp_num;
	}
	if (result == 0 || sign == num.sign)
		result.sign = '+';
	else
		result.sign = '-';
	return result;
}

BigInt BigInt::operator*(const int32_t &num) const{
	return (*this) * BigInt(num);
}

//BigInt operator*(const int32_t &num1, const BigInt &num2) {
//	return BigInt(num1) * num2;
//}

std::ostream &big_int::operator<<(std::ostream &out, const BigInt &num) {
	if (num.sign == '-')
		out << '-';
	for (size_t i = 0; i < num.size; i++)
		out << (char)(num.data[num.size - 1 - i] + '0');
	return out;
}
