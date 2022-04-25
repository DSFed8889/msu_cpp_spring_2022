#pragma once


#include <iostream>
#include <cstdint>


namespace matrix {
	class Matrix {
	public:
		class ProxyRow {
		private:
			int32_t *data_ = nullptr;
			int64_t columns_count_;
		public:
			explicit ProxyRow(int64_t);
			ProxyRow(const ProxyRow &);
			~ProxyRow();
			int32_t &operator[](int64_t) const;
			ProxyRow& operator=(const ProxyRow&);
			ProxyRow operator+(const ProxyRow&);
			ProxyRow& operator+=(const ProxyRow&);
			ProxyRow& operator*=(int32_t);
			bool operator==(const ProxyRow&);
			friend std::ostream& operator<<(std::ostream& out, const ProxyRow& row);
		};
		Matrix& operator=(const Matrix&);
		Matrix(int64_t, int64_t);
		Matrix(const Matrix&);
		~Matrix();
		[[nodiscard]] int64_t getRows() const;
		[[nodiscard]] int64_t getColumns() const;
		ProxyRow &operator[](int64_t) const;
		Matrix operator+(const Matrix&);
		Matrix& operator+=(const Matrix&);
		Matrix& operator*=(int32_t);
		bool operator==(const Matrix&);
		bool operator!=(const Matrix&);
		friend std::ostream& operator<<(std::ostream& out, const Matrix& matr);
	private:
		int64_t Max_size = 1000000000ull;
		int64_t rows_count_;
		int64_t columns_count_;
		ProxyRow *rows_ = nullptr;
	};
	std::ostream& operator<<(std::ostream& out, const Matrix::ProxyRow& row);
	std::ostream& operator<<(std::ostream& out, const Matrix& matr);
}
