#include <iostream>
#include "Matrix.hpp"
#include <cassert>

using namespace matrix;

int main() {
	const size_t rows = 5;
	const size_t cols = 3;
	
	Matrix m(rows, cols);
	
	assert(m.getRows() == 5);
	assert(m.getColumns() == 3);
	
	m[1][2] = 5; // строка 1, колонка 2
	double x = m[4][1];
	
	m *= 3; // умножение на число
	
	Matrix m1(rows, cols);
	
	if (m1 == m)
	{
	}
	Matrix m2 = m1 + m;
	std::cout << m2 << std::endl;
}