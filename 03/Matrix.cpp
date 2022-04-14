#include <iostream>
#include "Matrix.hpp"

using namespace matrix;

Matrix::ProxyRow::ProxyRow(size_t j = 0): columns_count_(j) {
	if (columns_count_ == 0)
		data_ = nullptr;
	else
		data_ = new int32_t[columns_count_];
	for (size_t i = 0; i < columns_count_; i++)
		data_[i] = 0;
}

Matrix::ProxyRow::ProxyRow(const Matrix::ProxyRow &new_row) {
	columns_count_ = new_row.columns_count_;
	if (columns_count_ == 0)
		data_ = nullptr;
	else
		data_ = new int32_t[columns_count_];
	for (size_t i = 0; i < columns_count_; i++)
		data_[i] = new_row.data_[i];
}

Matrix::ProxyRow::~ProxyRow() {
	if (data_ != nullptr)
		delete[] data_;
}

int32_t &Matrix::ProxyRow::operator[](size_t j) const{
	if (j < columns_count_)
		return data_[j];
	throw std::out_of_range("Too large column index");
}

Matrix::ProxyRow &Matrix::ProxyRow::operator=(const Matrix::ProxyRow &new_row) {
	columns_count_ = new_row.columns_count_;
	if (columns_count_ != 0) {
			data_ = new int32_t[columns_count_];
		for (size_t i = 0; i < columns_count_; i++)
			data_[i] = new_row.data_[i];
	}
	else
		data_ = nullptr;
	return *this;
}

Matrix::ProxyRow Matrix::ProxyRow::operator+(const Matrix::ProxyRow &row) {
	if (columns_count_ != row.columns_count_)
		throw std::logic_error("Not equal dimensions!");
	Matrix::ProxyRow new_row = row;
	for (size_t i = 0; i < row.columns_count_; i++)
		new_row.data_[i] += data_[i];
	return new_row;
}

Matrix::ProxyRow &Matrix::ProxyRow::operator+=(const Matrix::ProxyRow &row) {
	if (columns_count_ != row.columns_count_)
		throw std::logic_error("Not equal dimensions!");
	for (size_t i = 0; i < columns_count_; i++)
		data_[i] += row.data_[i];
	return *this;
}

Matrix::ProxyRow &Matrix::ProxyRow::operator*=(int32_t num) {
	for (size_t i = 0; i < columns_count_; i++)
		data_[i] *= num;
	return *this;
}

bool Matrix::ProxyRow::operator==(const Matrix::ProxyRow  &row) {
	if (columns_count_ != row.columns_count_)
		return false;
	for (size_t i = 0; i < columns_count_; i++)
		if (data_[i] != row.data_[i])
			return false;
	return true;
}

Matrix::Matrix(size_t rows_count, size_t columns_count): rows_count_(rows_count), columns_count_(columns_count) {
	if (rows_count_ * columns_count_ > Max_size) {
		rows_count_ = 0;
		columns_count_ = 0;
	}
	if (rows_count_ != 0) {
		try {
			rows_ = new Matrix::ProxyRow[rows_count_];
			for (size_t i = 0; i < rows_count_; i++)
				rows_[i] = Matrix::ProxyRow(columns_count);
		}
		catch(std::bad_alloc& e) {
			std::cerr << "Can't alloc memory!" << std::endl;
			rows_count_ = 0;
			columns_count_ = 0;
		}
	}
	else
		rows_ = nullptr;
}

Matrix::Matrix(const Matrix  &new_matr): rows_count_(new_matr.rows_count_),  columns_count_(new_matr.columns_count_){
	if (rows_count_ != 0) {
		try {
			rows_ = new Matrix::ProxyRow[rows_count_];
			for (size_t i = 0; i < rows_count_; i++)
				rows_[i] = new_matr.rows_[i];
		}
		catch(std::bad_alloc& e) {
			std::cerr << "Can't alloc memory!" << std::endl;
			rows_count_ = 0;
			columns_count_ = 0;
		}
	}
	else
		rows_ = nullptr;
}

Matrix::~Matrix() {
	if (rows_ != nullptr)
		delete[] rows_;
}

size_t Matrix::getRows() const {
	return rows_count_;
}

size_t Matrix::getColumns() const {
	return columns_count_;
}

Matrix::ProxyRow &Matrix::operator[](size_t i) const{
	if (i < rows_count_)
		return rows_[i];
	throw std::out_of_range("Too large row index");
}

Matrix &Matrix::operator=(const Matrix &new_matr) {
	rows_count_ = new_matr.rows_count_;
	columns_count_ = new_matr.columns_count_;
	if (rows_count_ != 0) {
		try {
			rows_ = new Matrix::ProxyRow[rows_count_];
			for (size_t i = 0; i < rows_count_; i++)
				rows_[i] = new_matr.rows_[i];
		}
		catch(std::bad_alloc& e) {
			std::cerr << "Can't alloc memory!" << std::endl;
			rows_count_ = 0;
			columns_count_ = 0;
		}
	}
	else
		rows_ = nullptr;
	return *this;
}

Matrix &Matrix::operator+=(const Matrix &matr) {
	if (rows_count_ != matr.rows_count_ || columns_count_ != matr.columns_count_)
		throw std::logic_error("Not equal dimensions!");
	for (size_t i = 0; i < rows_count_; i++)
		rows_[i] += matr.rows_[i];
	return *this;
}

Matrix Matrix::operator+(const Matrix &matr) {
	if (rows_count_ != matr.rows_count_ || columns_count_ != matr.columns_count_)
		throw std::logic_error("Not equal dimensions!");
	Matrix new_matr = matr;
	for (size_t i = 0; i < new_matr.rows_count_; i++)
		new_matr.rows_[i] += rows_[i];
	return new_matr;
}

Matrix &Matrix::operator*=(int32_t num) {
	for (size_t i = 0; i < rows_count_; i++)
		rows_[i] *= num;
	return *this;
}

bool Matrix::operator==(const Matrix &matr) {
	if (rows_count_ != matr.rows_count_ || columns_count_ != matr.columns_count_)
		return false;
	for (size_t i = 0; i < rows_count_; i++)
		if (!(rows_[i] == matr.rows_[i]))
			return false;
	return true;
}

bool Matrix::operator!=(const Matrix &matr) {
	return !((*this) == matr);
}

std::ostream &matrix::operator<<(std::ostream &out, const Matrix::ProxyRow &row) {
	out << "[" << row.data_[0];
	for (size_t i = 1; i < row.columns_count_; i++)
		out << ", " << row.data_[i];
	out << "]";
	return out;
}

std::ostream &matrix::operator<<(std::ostream &out, const Matrix &matr) {
	out << "Matrix with dimension " << matr.rows_count_ << "x" << matr.columns_count_ << std::endl;
	out << "[" << matr.rows_[0] << std::endl;
	for (size_t i = 1; i < matr.rows_count_ - 1; i++)
		out << ' ' << matr.rows_[i] << std::endl;
	out << ' ' << matr.rows_[matr.rows_count_ - 1] << "]" << std::endl;
	return out;
}
