CC=g++-10
FLAGS=-std=c++20 -Wall -pedantic -Wextra -Werror
TEST_LIBS=-lgtest_main -lgtest -lpthread

.PHONY: all

all: clean test_bin test

ThreadPool.o: ThreadPool.cpp ThreadPool.hpp
	$(CC) $(FLAGS) ThreadPool.cpp -c

test_bin: ThreadPool.o ThreadPoolTest.cpp
	$(CC) $(FLAGS) ThreadPool.o ThreadPoolTest.cpp -o test_bin $(TEST_LIBS)

test: test_bin
	./test_bin

clean:
	rm -f *.o ThreadPool
