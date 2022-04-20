#pragma once


#include <iostream>
#include <string>
#include <cstdint>


namespace big_int {
	class BigInt {
		char* data = nullptr;
		char sign;
		size_t size = 0;
	public:
		BigInt(int32_t num = 0);
		BigInt(std::string);
		BigInt(const BigInt&);
		BigInt(BigInt&&);
		~BigInt();
		bool operator>(const BigInt&) const;
		bool operator>=(const BigInt&) const;
		bool operator<(const BigInt&) const;
		bool operator<=(const BigInt&) const;
		bool operator==(const BigInt&) const;
		bool operator!=(const BigInt&) const;
		BigInt& operator=(const BigInt&);
		BigInt& operator=(BigInt&&);
		BigInt operator+(const BigInt&) const;
		BigInt operator+(const int32_t&) const;
		friend BigInt operator+(const int32_t&, const BigInt&);
		BigInt operator-() const;
		BigInt operator-(const BigInt&) const;
		BigInt operator-(const int32_t&) const;
		friend BigInt operator-(const int32_t&, const BigInt&);
		BigInt operator*(const BigInt&) const;
		BigInt operator*(const int32_t&) const;
		friend BigInt operator*(const int32_t&, const BigInt&);
		friend std::ostream& operator<<(std::ostream&,const BigInt&);
	};
	BigInt operator + (const int32_t&, const BigInt&);
	BigInt operator - (const int32_t&, const BigInt&);
	BigInt operator * (const int32_t&, const BigInt&);
	std::ostream& operator << (std::ostream&,const BigInt&);
}