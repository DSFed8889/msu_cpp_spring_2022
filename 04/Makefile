CC=g++-10
FLAGS=-std=c++20 -Wall -pedantic -Wextra -Werror
TEST_LIBS=-lgtest_main -lgtest -lpthread

clean:

all: test_bin test main_bin main

BigInt.o: BigInt.cpp BigInt.hpp
	$(CC) $(FLAGS) BigInt.cpp -c

main_bin: BigInt.o main.cpp
	$(CC) $(FLAGS) BigInt.o main.cpp -o main_bin

main: main_bin
	./main_bin

test_bin: BigInt.o TestBigInt.cpp
	$(CC) $(FLAGS) BigInt.o TestBigInt.cpp -o test_bin $(TEST_LIBS)

test: test_bin
	./test_bin

clean:
	rm -f *.o BigInt
