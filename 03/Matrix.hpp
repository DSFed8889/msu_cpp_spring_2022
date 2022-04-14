#pragma once


#include <iostream>
#include <cstdint>


namespace matrix {
	class Matrix {
	public:
		class ProxyRow {
		private:
			int32_t *data_ = nullptr;
			size_t columns_count_;
		public:
			explicit ProxyRow(size_t);
			ProxyRow(const ProxyRow &);
			~ProxyRow();
			int32_t &operator[](size_t) const;
			ProxyRow& operator=(const ProxyRow&);
			ProxyRow operator+(const ProxyRow&);
			ProxyRow& operator+=(const ProxyRow&);
			ProxyRow& operator*=(int32_t);
			bool operator==(const ProxyRow&);
			friend std::ostream& operator<<(std::ostream& out, const ProxyRow& row);
		};
		Matrix& operator=(const Matrix&);
		Matrix(size_t, size_t);
		Matrix(const Matrix&);
		~Matrix();
		[[nodiscard]] size_t getRows() const;
		[[nodiscard]] size_t getColumns() const;
		ProxyRow &operator[](size_t) const;
		Matrix operator+(const Matrix&);
		Matrix& operator+=(const Matrix&);
		Matrix& operator*=(int32_t);
		bool operator==(const Matrix&);
		bool operator!=(const Matrix&);
		friend std::ostream& operator<<(std::ostream& out, const Matrix& matr);
	private:
		size_t Max_size = 1000000000ull;
		size_t rows_count_;
		size_t columns_count_;
		ProxyRow *rows_ = nullptr;
	};
	std::ostream& operator<<(std::ostream& out, const Matrix::ProxyRow& row);
	std::ostream& operator<<(std::ostream& out, const Matrix& matr);
}
