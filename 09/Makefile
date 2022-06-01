CC=g++-10
FLAGS=-std=c++20 -Wall -pedantic -Wextra -Werror
TEST_LIBS=-lgtest_main -lgtest -lpthread

.PHONY: all

all: clean test_bin test

ExtSort.o: ExtSort.cpp ExtSort.hpp
	$(CC) $(FLAGS) ExtSort.cpp -c

test_bin: ExtSort.o ExtSortTest.cpp
	$(CC) $(FLAGS) ExtSort.o ExtSortTest.cpp -o test_bin $(TEST_LIBS)

test: test_bin
	./test_bin

clean:
	rm test_bin -f *.o ExtSort
