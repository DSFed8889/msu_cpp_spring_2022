#include <iostream>
#include <functional>
#include <string>
#include <vector>
#include <typeinfo>
#include <gtest/gtest.h>
#include <sstream>
#include "Matrix.hpp"

class TestMatrix : public ::testing::Test {
public:
	std::streambuf* orig_buf;
protected:
	void SetUp() {
		// get underlying buffer
		orig_buf = std::cerr.rdbuf();
		
		// set null
		std::cerr.rdbuf(NULL);
		std::cout << "SetUp" << std::endl;
	}
	void TearDown() {
		
		// restore buffer
		std::cerr.rdbuf(orig_buf);
		std::cout << "TearDown" << std::endl;
	}
};

TEST_F(TestMatrix, test_cout) {
	std::ostringstream test_out_buf;

	matrix::Matrix matrix(0, 0);
	test_out_buf << matrix;
	ASSERT_EQ(test_out_buf.str(), "Empty matrix\n");
	test_out_buf.str("");
	test_out_buf.clear();

	matrix = matrix::Matrix(1, 0);
	test_out_buf << matrix;
	ASSERT_EQ(test_out_buf.str(), "Empty matrix\n");
	test_out_buf.str("");
	test_out_buf.clear();

	matrix = matrix::Matrix(0, 1);
	test_out_buf << matrix;
	ASSERT_EQ(test_out_buf.str(), "Empty matrix\n");
	test_out_buf.str("");
	test_out_buf.clear();

	matrix = matrix::Matrix(1, 1);
	test_out_buf << matrix;
	ASSERT_EQ(test_out_buf.str(), "Matrix with dimension 1x1:\n[[0]]\n");
	test_out_buf.str("");
	test_out_buf.clear();

	matrix = matrix::Matrix(1, 3);
	test_out_buf << matrix;
	ASSERT_EQ(test_out_buf.str(), "Matrix with dimension 1x3:\n[[0, 0, 0]]\n");
	test_out_buf.str("");
	test_out_buf.clear();
	for (int64_t i = 0; i < matrix.getRows(); ++i)
		for (int64_t j = 0; j < matrix.getColumns(); ++j)
			matrix[i][j] = (i+1)*(j+1);
	test_out_buf << matrix;
	ASSERT_EQ(test_out_buf.str(), "Matrix with dimension 1x3:\n[[1, 2, 3]]\n");
	test_out_buf.str("");
	test_out_buf.clear();

	matrix = matrix::Matrix(3, 1);
	test_out_buf << matrix;
	ASSERT_EQ(test_out_buf.str(), "Matrix with dimension 3x1:\n[[0]\n [0]\n [0]]\n");
	test_out_buf.str("");
	test_out_buf.clear();
	for (int64_t i = 0; i < matrix.getRows(); ++i)
		for (int64_t j = 0; j < matrix.getColumns(); ++j)
			matrix[i][j] = (i+1)*(j+1);
	test_out_buf << matrix;
	ASSERT_EQ(test_out_buf.str(), "Matrix with dimension 3x1:\n[[1]\n [2]\n [3]]\n");
	test_out_buf.str("");
	test_out_buf.clear();

	matrix = matrix::Matrix(2, 3);
	test_out_buf << matrix;
	ASSERT_EQ(test_out_buf.str(), "Matrix with dimension 2x3:\n[[0, 0, 0]\n [0, 0, 0]]\n");
	test_out_buf.str("");;
	test_out_buf.clear();
	for (int64_t i = 0; i < matrix.getRows(); ++i)
		for (int64_t j = 0; j < matrix.getColumns(); ++j)
			matrix[i][j] = (i+1)*(j+1);
	test_out_buf << matrix;
	ASSERT_EQ(test_out_buf.str(), "Matrix with dimension 2x3:\n[[1, 2, 3]\n [2, 4, 6]]\n");
	test_out_buf.str("");;
	test_out_buf.clear();
}

TEST_F(TestMatrix, test_constructor) {
	ASSERT_NO_THROW(matrix::Matrix(0, 0));
	matrix::Matrix matrix1(0, 0);
	ASSERT_EQ(matrix1.getRows(), 0);
	ASSERT_EQ(matrix1.getColumns(), 0);

	ASSERT_NO_THROW(matrix::Matrix(1, 0));
	matrix::Matrix matrix2(1, 0);
	ASSERT_EQ(matrix2.getRows(), 1);
	ASSERT_EQ(matrix2.getColumns(), 0);

	ASSERT_NO_THROW(matrix::Matrix(0, 1));
	matrix::Matrix matrix3(0, 1);
	ASSERT_EQ(matrix3.getRows(), 0);
	ASSERT_EQ(matrix3.getColumns(), 1);

	ASSERT_NO_THROW(matrix::Matrix(1, 1));
	matrix::Matrix matrix4(1, 1);
	ASSERT_EQ(matrix4.getRows(), 1);
	ASSERT_EQ(matrix4.getColumns(), 1);

	ASSERT_NO_THROW(matrix::Matrix(1, 500));
	matrix::Matrix matrix5(1, 500);
	ASSERT_EQ(matrix5.getRows(), 1);
	ASSERT_EQ(matrix5.getColumns(), 500);

	ASSERT_NO_THROW(matrix::Matrix(333, 1));
	matrix::Matrix matrix6(333, 1);
	ASSERT_EQ(matrix6.getRows(), 333);
	ASSERT_EQ(matrix6.getColumns(), 1);

	ASSERT_NO_THROW(matrix::Matrix(17, 200));
	matrix::Matrix matrix7(17, 200);
	ASSERT_EQ(matrix7.getRows(), 17);
	ASSERT_EQ(matrix7.getColumns(), 200);

	ASSERT_NO_THROW(matrix::Matrix(2, 1000000000000));
	matrix::Matrix matrix8(2, 1000000000000);
	ASSERT_EQ(matrix8.getRows(), 0);
	ASSERT_EQ(matrix8.getColumns(), 0);

	ASSERT_NO_THROW(matrix::Matrix(10000000000000, 2));
	matrix::Matrix matrix9(2, 1000000000000);
	ASSERT_EQ(matrix9.getRows(), 0);
	ASSERT_EQ(matrix9.getColumns(), 0);

	ASSERT_NO_THROW(matrix::Matrix(10000000000000, 100000000000));
	matrix::Matrix matrix10(10000000000000, 100000000000);
	ASSERT_EQ(matrix10.getRows(), 0);
	ASSERT_EQ(matrix10.getColumns(), 0);

	ASSERT_NO_THROW(matrix::Matrix(0, 1000000000000));
	matrix::Matrix matrix11(0, 1000000000000);
	ASSERT_EQ(matrix11.getRows(), 0);
	ASSERT_EQ(matrix11.getColumns(), 1000000000000);

	ASSERT_NO_THROW(matrix::Matrix(-12, 6));
	matrix::Matrix matrix12(-12, 6);
	ASSERT_EQ(matrix12.getRows(), 0);
	ASSERT_EQ(matrix12.getColumns(), 0);

	ASSERT_NO_THROW(matrix::Matrix(9, -1223));
	matrix::Matrix matrix13(9, -1223);
	ASSERT_EQ(matrix13.getRows(), 0);
	ASSERT_EQ(matrix13.getColumns(), 0);

	ASSERT_NO_THROW(matrix::Matrix(-23423, -17890));
	matrix::Matrix matrix14(-23423, -17890);
	ASSERT_EQ(matrix14.getRows(), 0);
	ASSERT_EQ(matrix14.getColumns(), 0);
}

TEST_F(TestMatrix, test_getRows_getColumns) {
	matrix::Matrix matrix1(0, 0);
	ASSERT_EQ(matrix1.getRows(), 0);
	ASSERT_EQ(matrix1.getColumns(), 0);

	matrix::Matrix matrix2(1, 1);
	ASSERT_EQ(matrix2.getRows(), 1);
	ASSERT_EQ(matrix2.getColumns(), 1);

	matrix::Matrix matrix3(1, 0);
	ASSERT_EQ(matrix3.getRows(), 1);
	ASSERT_EQ(matrix3.getColumns(), 0);

	matrix::Matrix matrix4(1, 1);
	ASSERT_EQ(matrix4.getRows(), 1);
	ASSERT_EQ(matrix4.getColumns(), 1);

	matrix::Matrix matrix5(1, 500);
	ASSERT_EQ(matrix5.getRows(), 1);
	ASSERT_EQ(matrix5.getColumns(), 500);

	matrix::Matrix matrix6(333, 1);
	ASSERT_EQ(matrix6.getRows(), 333);
	ASSERT_EQ(matrix6.getColumns(), 1);

	matrix::Matrix matrix7(17, 200);
	ASSERT_EQ(matrix7.getRows(), 17);
	ASSERT_EQ(matrix7.getColumns(), 200);

	matrix::Matrix matrix8(14, 18);
	ASSERT_EQ(matrix8.getRows(), 14);
	ASSERT_EQ(matrix8.getColumns(), 18);

	matrix::Matrix matrix9(10000, 100000);
	ASSERT_EQ(matrix9.getRows(), 10000);
	ASSERT_EQ(matrix9.getColumns(), 100000);
}

TEST_F(TestMatrix, test_get_items) {
	matrix::Matrix matrix1(0, 0);
	ASSERT_THROW(matrix1[0][0], std::out_of_range);

	matrix::Matrix matrix2(1, 1);
	ASSERT_NO_THROW(matrix2[0][0]);

	matrix::Matrix matrix3(1, 1);
	ASSERT_THROW(matrix3[1][0], std::out_of_range);

	matrix::Matrix matrix4(1, 1);
	ASSERT_THROW(matrix4[0][1], std::out_of_range);

	matrix::Matrix matrix5(1, 1);
	ASSERT_THROW(matrix5[1][1], std::out_of_range);

	matrix::Matrix matrix6(8, 7);
	ASSERT_NO_THROW(matrix6[1][2] = 18);
	for (size_t i = 0; i < 1; i++)
		for (size_t j = 0; j < 7; j++) {
			ASSERT_NO_THROW(matrix6[i][j]);
			ASSERT_EQ(matrix6[i][j], 0);
		}
	ASSERT_NO_THROW(matrix6[1][0]);
	ASSERT_EQ(matrix6[1][0], 0);
	ASSERT_NO_THROW(matrix6[1][1]);
	ASSERT_EQ(matrix6[1][1], 0);
	ASSERT_NO_THROW(matrix6[1][2]);
	ASSERT_EQ(matrix6[1][2], 18);
	for (size_t i = 3; i < 7; i++) {
		ASSERT_NO_THROW(matrix6[1][i]);
		ASSERT_EQ(matrix6[1][i], 0);
	}
	for (size_t i = 2; i < 8; i++)
		for (size_t j = 0; j < 7; j++) {
			ASSERT_NO_THROW(matrix6[i][j]);
			ASSERT_EQ(matrix6[i][j], 0);
			matrix6[i][j] = i*j;
			ASSERT_NO_THROW(matrix6[i][j]);
			ASSERT_EQ(matrix6[i][j], i*j);
		}
	ASSERT_THROW(matrix6[8][6], std::out_of_range);
}

TEST_F(TestMatrix, test_matrix_compare) {
	matrix::Matrix matrix1(8, 9);
	for (size_t i = 0; i < 8; i++)
		for (size_t j = 0; j < 9; j++)
			matrix1[i][j] = i * j;

	matrix::Matrix matrix2(8, 9);
	for (size_t i = 0; i < 8; i++)
		for (size_t j = 0; j < 9; j++)
			matrix2[i][j] = i * j;

	matrix::Matrix matrix3(6, 9);
	for (size_t i = 0; i < 6; i++)
		for (size_t j = 0; j < 9; j++)
			matrix3[i][j] = i * j;

	matrix::Matrix matrix4(8, 4);
	for (size_t i = 0; i < 8; i++)
		for (size_t j = 0; j < 4; j++)
			matrix4[i][j] = i * j;

	matrix::Matrix matrix5(2, 4);
	for (size_t i = 0; i < 2; i++)
		for (size_t j = 0; j < 4; j++)
			matrix5[i][j] = i * j;

	matrix::Matrix matrix6(8, 9);
	for (size_t i = 0; i < 7; i++)
		for (size_t j = 0; j < 9; j++)
			matrix6[i][j] = i * j;

	matrix::Matrix matrix7(11, 9);
	for (size_t i = 0; i < 8; i++)
		for (size_t j = 0; j < 9; j++)
			matrix7[i][j] = i * j;

	matrix::Matrix matrix8(8, 12);
	for (size_t i = 0; i < 8; i++)
		for (size_t j = 0; j < 9; j++)
			matrix8[i][j] = i * j;

	matrix::Matrix matrix9(14, 15);
	for (size_t i = 0; i < 8; i++)
		for (size_t j = 0; j < 9; j++)
			matrix9[i][j] = i * j;

	matrix::Matrix matrix10(11, 9);
	for (size_t i = 0; i < 11; i++)
		for (size_t j = 0; j < 9; j++)
			matrix10[i][j] = i * j;

	matrix::Matrix matrix11(8, 12);
	for (size_t i = 0; i < 8; i++)
		for (size_t j = 0; j < 12; j++)
			matrix11[i][j] = i * j;

	matrix::Matrix matrix12(14, 15);
	for (size_t i = 0; i < 14; i++)
		for (size_t j = 0; j < 15; j++)
			matrix12[i][j] = i * j;

	matrix::Matrix matrix13(0, 0);
	matrix::Matrix matrix14(1, 200);
	matrix::Matrix matrix15(200, 1);

	ASSERT_TRUE(matrix14 != matrix15);
	ASSERT_FALSE(matrix14 == matrix15);

	ASSERT_TRUE(matrix1 == matrix2);
	ASSERT_FALSE(matrix1 != matrix2);
	ASSERT_TRUE(matrix1 != matrix3);
	ASSERT_FALSE(matrix1 == matrix3);
	ASSERT_TRUE(matrix1 != matrix4);
	ASSERT_FALSE(matrix1 == matrix4);
	ASSERT_TRUE(matrix1 != matrix5);
	ASSERT_FALSE(matrix1 == matrix5);
	ASSERT_TRUE(matrix1 != matrix6);
	ASSERT_FALSE(matrix1 == matrix6);
	ASSERT_TRUE(matrix1 != matrix7);
	ASSERT_FALSE(matrix1 == matrix7);
	ASSERT_TRUE(matrix1 != matrix8);
	ASSERT_FALSE(matrix1 == matrix8);
	ASSERT_TRUE(matrix1 != matrix9);
	ASSERT_FALSE(matrix1 == matrix9);
	ASSERT_TRUE(matrix1 != matrix10);
	ASSERT_FALSE(matrix1 == matrix10);
	ASSERT_TRUE(matrix1 != matrix11);
	ASSERT_FALSE(matrix1 == matrix11);
	ASSERT_TRUE(matrix1 != matrix12);
	ASSERT_FALSE(matrix1 == matrix12);
	ASSERT_TRUE(matrix1 != matrix13);
	ASSERT_FALSE(matrix1 == matrix13);

	ASSERT_TRUE(matrix2 == matrix1);
	ASSERT_FALSE(matrix2 != matrix1);
	ASSERT_TRUE(matrix3 != matrix1);
	ASSERT_FALSE(matrix3 == matrix1);
	ASSERT_TRUE(matrix4 != matrix1);
	ASSERT_FALSE(matrix4 == matrix1);
	ASSERT_TRUE(matrix5 != matrix1);
	ASSERT_FALSE(matrix5 == matrix1);
	ASSERT_TRUE(matrix6 != matrix1);
	ASSERT_FALSE(matrix6 == matrix1);
	ASSERT_TRUE(matrix7 != matrix1);
	ASSERT_FALSE(matrix7 == matrix1);
	ASSERT_TRUE(matrix8 != matrix1);
	ASSERT_FALSE(matrix8 == matrix1);
	ASSERT_TRUE(matrix9 != matrix1);
	ASSERT_FALSE(matrix9 == matrix1);
	ASSERT_TRUE(matrix10 != matrix1);
	ASSERT_FALSE(matrix10 == matrix1);
	ASSERT_TRUE(matrix11 != matrix1);
	ASSERT_FALSE(matrix11 == matrix1);
	ASSERT_TRUE(matrix12 != matrix1);
	ASSERT_FALSE(matrix12 == matrix1);
	ASSERT_TRUE(matrix13 != matrix1);
	ASSERT_FALSE(matrix13 == matrix1);
}

TEST_F(TestMatrix, test_assignment) {
	matrix::Matrix matrix1(8, 9);
	for (size_t i = 0; i < 8; i++)
		for (size_t j = 0; j < 9; j++)
			matrix1[i][j] = i * j;

	matrix::Matrix matrix2(8, 9);
	ASSERT_TRUE(matrix1 != matrix2);
	matrix2 = matrix1;
	ASSERT_TRUE(matrix1 == matrix2);

	matrix::Matrix matrix3(2, 4);
	ASSERT_TRUE(matrix1 != matrix3);
	matrix3 = matrix1;
	ASSERT_TRUE(matrix1 == matrix3);

	matrix::Matrix matrix4(0, 0);
	matrix::Matrix matrix5(0, 0);
	ASSERT_TRUE(matrix4 != matrix2);
	matrix2 = matrix4;
	ASSERT_TRUE(matrix4 == matrix2);
	matrix4 = matrix1;
	ASSERT_TRUE(matrix4 == matrix1);
	matrix3 = matrix1;
	ASSERT_TRUE(matrix4 == matrix3);
	matrix1 = matrix5;
	ASSERT_TRUE(matrix4 != matrix1);
	ASSERT_TRUE(matrix4 == matrix3);
}

TEST_F(TestMatrix, test_multiply) {
	matrix::Matrix matrix1(8, 9);
	matrix::Matrix matrix2(8, 9);
	ASSERT_TRUE(matrix1 == matrix2);
	ASSERT_NO_THROW(matrix1 *= 6);
	ASSERT_TRUE(matrix1 == matrix2);
	for (size_t i = 0; i < 8; i++)
		for (size_t j = 0; j < 9; j++)
			matrix1[i][j] = 1;
	matrix2 = matrix1;
	ASSERT_TRUE(matrix1 == matrix2);
	matrix2 *= 8;
	ASSERT_FALSE(matrix1 == matrix2);
	for (size_t i = 0; i < 8; i++)
		for (size_t j = 0; j < 9; j++) {
			ASSERT_EQ(matrix1[i][j], 1);
			ASSERT_EQ(matrix2[i][j], 8);
		}
	matrix::Matrix matrix3(8, 9);
	matrix2 *= 0;
	ASSERT_TRUE(matrix3 == matrix2);
	int32_t very_big_number = 100000000;
	ASSERT_NO_THROW(matrix1 *= very_big_number);
	for (size_t i = 0; i < 8; i++)
		for (size_t j = 0; j < 9; j++)
			ASSERT_EQ(matrix1[i][j], very_big_number);
	int32_t square_very_big_number = very_big_number * very_big_number;
	ASSERT_NO_THROW(matrix1 *= very_big_number);
	for (size_t i = 0; i < 8; i++)
		for (size_t j = 0; j < 9; j++)
			ASSERT_EQ(matrix1[i][j], square_very_big_number);
}

TEST_F(TestMatrix, test_plus) {
	matrix::Matrix matrix1(8, 9);
	matrix::Matrix matrix2(8, 9);
	ASSERT_TRUE(matrix1 == matrix2);
	matrix::Matrix matrix3 = matrix1 + matrix2;
	ASSERT_TRUE(matrix1 == matrix2);
	ASSERT_TRUE(matrix1 == matrix3);
	for (size_t i = 0; i < 8; i++)
		for (size_t j = 0; j < 9; j++)
			matrix1[i][j] = 100;
	matrix2 = matrix1;
	matrix2 *= -1;
	ASSERT_NO_THROW(matrix1 + matrix2);
	ASSERT_TRUE(matrix3 == matrix1 + matrix2);
	matrix2 *= -1;
	matrix3 += matrix2;
	ASSERT_TRUE(matrix3 == matrix2);
	matrix::Matrix matrix4(2, 2);
	matrix::Matrix matrix5(0, 0);
	ASSERT_THROW(matrix1 += matrix4, std::logic_error);
	ASSERT_THROW(matrix1 + matrix4, std::logic_error);
	ASSERT_THROW(matrix1 += matrix5, std::logic_error);
	ASSERT_THROW(matrix1 + matrix5, std::logic_error);
}


int main(int argc, char *argv[]) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}