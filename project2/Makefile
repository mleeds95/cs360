# File: Makefile
# Author: Matthew Leeds
# Last Edit: 2015-02-02

CC=g++
CFLAGS=
OBJ=main.o StringData.o ManufacturerData.o

project2: $(OBJ)
	$(CC) $(CFLAGS) -o project2 $(OBJ)

main.o: main.cpp ManufacturerData.cpp StringData.cpp
	$(CC) $(CFLAGS) -c main.cpp

ManufacturerData.o: ManufacturerData.cpp StringData.cpp
	$(CC) $(CFLAGS) -c ManufacturerData.cpp

StringData.o: StringData.cpp
	$(CC) $(CFLAGS) -c StringData.cpp

clean:
	rm project2 *.o
