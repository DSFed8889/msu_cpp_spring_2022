CC=g++-10
FLAGS=-std=c++20 -Wall -pedantic -Wextra -Werror
TEST_LIBS=-lgtest_main -lgtest -lpthread

all: test_bin test

allocator.o: allocator.cpp allocator.hpp
	$(CC) $(FLAGS) allocator.cpp -c
	
test_bin: allocator.o test.cpp
	$(CC) $(FLAGS) allocator.o test.cpp -o test_bin $(TEST_LIBS)

test:
	./test_bin
