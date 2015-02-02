# File: Makefile
# Author: Matthew Leeds
# Last Edit: 2015-02-01

CC=g++
CFLAGS=
OBJ=main.o ManufacturerData.o trimQuotes.o

project2: $(OBJ)
	$(CC) $(CFLAGS) -o project2 $(OBJ)

main.o: main.cpp ManufacturerData.cpp
	$(CC) $(CFLAGS) -c main.cpp

ManufacturerData.o: ManufacturerData.cpp
	$(CC) $(CFLAGS) -c ManufacturerData.cpp

trimQuotes.o: trimQuotes.cpp
	$(CC) $(CFLAGS) -c trimQuotes.cpp

clean:
	rm project2 *.o
