CC=g++-10
FLAGS=-std=c++20 -Wall -pedantic -Wextra -Werror
TEST_LIBS=-lgtest_main -lgtest -lpthread

all: test_bin test main_bin main

test_bin: str_format.hpp test_str_format.cpp
	$(CC) $(FLAGS) test_str_format.cpp -o test_bin $(TEST_LIBS)

main_bin: str_format.hpp main.cpp
	$(CC) $(FLAGS) main.cpp -o main_bin

main: main_bin
	./main_bin

test: test_bin
	./test_bin

clean:
	rm -rf test_bin main_bin
