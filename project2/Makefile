# File: Makefile
# Author: Matthew Leeds
# Last Edit: 2015-02-08

CC=g++
CFLAGS=-Wall
OBJ=main.o ManufacturerData.o SalesData.o stringFunctions.o

project2: $(OBJ)
	$(CC) $(CFLAGS) -o project2 $(OBJ)

main.o: main.cpp ManufacturerData.cpp SalesData.cpp stringFunctions.cpp
	$(CC) $(CFLAGS) -c main.cpp

ManufacturerData.o: ManufacturerData.cpp stringFunctions.cpp
	$(CC) $(CFLAGS) -c ManufacturerData.cpp

SalesData.o: SalesData.cpp ManufacturerData.cpp stringFunctions.cpp
	$(CC) $(CFLAGS) -c SalesData.cpp

stringFunctions.o: stringFunctions.cpp
	$(CC) $(CFLAGS) -c stringFunctions.cpp

clean:
	rm project2 *.o
