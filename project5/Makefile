# File: Makefile
# Author: Matthew Leeds
# Last Edit: 2015-03-28

CC=clang++-3.5
CFLAGS=-Wall -g -std=c++98
OBJ=main.o Boggle.o

project5: $(OBJ)
	$(CC) $(CFLAGS) -o project5 $(OBJ)

main.o: main.cpp Boggle.cpp
	$(CC) $(CFLAGS) -c main.cpp Boggle.cpp

Boggle.o: Boggle.cpp
	$(CC) $(CFLAGS) -c Boggle.cpp

clean:
	rm project5 *.o
