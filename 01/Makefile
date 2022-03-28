CC=g++-10
FLAGS=-std=c++20 -Wall -pedantic -Wextra -Werror
TEST_LIBS=-lgtest_main -lgtest -lpthread

all: test_bin test
	
test_bin: allocator.hpp test.cpp
	$(CC) $(FLAGS) allocator.hpp test.cpp -o test_bin $(TEST_LIBS)

test:
	./test_bin
