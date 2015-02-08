# File: Makefile
# Author: Matthew Leeds
# Last Edit: 2015-02-03

CC=g++
CFLAGS=-Wall
OBJ=main.o ManufacturerData.o stringFunctions.o

project2: $(OBJ)
	$(CC) $(CFLAGS) -o project2 $(OBJ)

main.o: main.cpp ManufacturerData.cpp stringFunctions.cpp
	$(CC) $(CFLAGS) -c main.cpp

ManufacturerData.o: ManufacturerData.cpp stringFunctions.cpp
	$(CC) $(CFLAGS) -c ManufacturerData.cpp

stringFunctions.o: stringFunctions.cpp
	$(CC) $(CFLAGS) -c stringFunctions.cpp

clean:
	rm project2 *.o
