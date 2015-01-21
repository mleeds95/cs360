# File: Makefile
# Author: Matthew Leeds
# Last Edit: 2015-01-20

CC=g++
CFLAGS=-std=c++11
OBJ=main.o matrix.o

project1: $(OBJ)
	$(CC) $(CFLAGS) -o project1 $(OBJ)

main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp

matrix.o: matrix.cpp
	$(CC) $(CFLAGS) -c matrix.cpp

clean:
	rm project1 *.o
