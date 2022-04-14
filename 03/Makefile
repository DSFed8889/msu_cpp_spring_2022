CC=g++-10
FLAGS=-std=c++20 -Wall -pedantic -Wextra -Werror
TEST_LIBS=-lgtest_main -lgtest -lpthread

all: test_bin test main_bin main

Matrix.o: Matrix.cpp Matrix.hpp
	$(CC) $(FLAGS) Matrix.cpp -c

test_bin: Matrix.o test_Matrix.cpp
	$(CC) $(FLAGS) Matrix.o test_Matrix.cpp -o test_bin $(TEST_LIBS)

main_bin: Matrix.o main.cpp
	$(CC) $(FLAGS) Matrix.o main.cpp -o main_bin

main: main_bin
	valgrind ./main_bin

test: test_bin
	./test_bin
