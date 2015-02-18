# File: Makefile
# Author: Matthew Leeds
# Last Edit: 2015-02-17

CC=g++
CFLAGS=-Wall
OBJ=main.o ManufacturerData.o SalesData.o stringFunctions.o \
	StaticHashTable.o

project3: $(OBJ)
	$(CC) $(CFLAGS) -o project3 $(OBJ)

main.o: main.cpp ManufacturerData.cpp SalesData.cpp stringFunctions.cpp
	$(CC) $(CFLAGS) -c main.cpp

ManufacturerData.o: ManufacturerData.cpp stringFunctions.cpp
	$(CC) $(CFLAGS) -c ManufacturerData.cpp

SalesData.o: SalesData.cpp ManufacturerData.cpp stringFunctions.cpp
	$(CC) $(CFLAGS) -c SalesData.cpp

stringFunctions.o: stringFunctions.cpp
	$(CC) $(CFLAGS) -c stringFunctions.cpp

StaticHashTable.o: StaticHashTable.cpp
	$(CC) $(CFLAGS) -c StaticHashTable.cpp

.PHONY: clean

clean:
	rm project3 *.o
