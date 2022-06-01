CC=g++-10
FLAGS=-std=c++20 -Wall -pedantic -Wextra -Werror
TEST_LIBS=-lgtest_main -lgtest -lpthread

.PHONY: all

all: clean test_bin test

Vector.o: Vector.cpp Vector.hpp Vector.tpp
	$(CC) $(FLAGS) Vector.cpp -c

test_bin: Vector.o VectorTest.cpp
	$(CC) $(FLAGS) Vector.o VectorTest.cpp -o test_bin $(TEST_LIBS)

test: test_bin
	./test_bin

clean:
	rm test_bin -f *.o Vector
