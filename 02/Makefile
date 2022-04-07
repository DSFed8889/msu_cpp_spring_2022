CC=g++-10
FLAGS=-std=c++20 -Wall -pedantic -Wextra -Werror
TEST_LIBS=-lgtest_main -lgtest -lpthread

all: test_bin test main_bin main

parser.o: parser.cpp parser.hpp
	$(CC) $(FLAGS) parser.cpp -c

test_bin: parser.o test_parser.cpp
	$(CC) $(FLAGS) parser.o test_parser.cpp -o test_bin $(TEST_LIBS)

main_bin: parser.o main.cpp
	$(CC) $(FLAGS) parser.o main.cpp -o main_bin

main: main_bin
	./main_bin

test: test_bin
	./test_bin
