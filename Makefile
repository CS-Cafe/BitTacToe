CC = clang++
CFLAGS = -std=c++20 -O3 -Wall -DNDEBUG -march=native

bit: main.cpp
	$(CC) $(CFLAGS) -o $@ $^
