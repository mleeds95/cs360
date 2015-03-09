# File: Makefile
# Author: Matthew Leeds
# Last Edit: 2015-03-09

CC=g++
CFLAGS=-Wall -g -std=c++98
OBJ=main.o Schedule.o

project4: $(OBJ)
	$(CC) $(CFLAGS) -o project4 $(OBJ)

main.o: main.cpp Schedule.cpp
	$(CC) $(CFLAGS) -c main.cpp Schedule.cpp

Schedule.o: Schedule.cpp
	$(CC) $(CFLAGS) -c Schedule.cpp

clean:
	rm project4 *.o
