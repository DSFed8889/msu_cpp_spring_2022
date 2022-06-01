CC=g++-10
FLAGS=-std=c++20 -Wall -pedantic -Wextra -Werror
TEST_LIBS=-lgtest_main -lgtest -lpthread

.PHONY: all

all: clean test_bin test

Serializer.o: Serializer.cpp Serializer.hpp Serializer.tpp
	$(CC) $(FLAGS) Serializer.cpp -c

test_bin: Serializer.o SerializerTest.cpp
	$(CC) $(FLAGS) Serializer.o SerializerTest.cpp -o test_bin $(TEST_LIBS)

test: test_bin
	./test_bin

clean:
	rm -rf test_bin
