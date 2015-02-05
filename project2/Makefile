# File: Makefile
# Author: Matthew Leeds
# Last Edit: 2015-02-03

CC=g++
CFLAGS=
OBJ=main.o StringArray.o ManufacturerData.o trimQuotes.o

project2: $(OBJ)
	$(CC) $(CFLAGS) -o project2 $(OBJ)

main.o: main.cpp ManufacturerData.cpp StringArray.cpp trimQuotes.cpp
	$(CC) $(CFLAGS) -c main.cpp

ManufacturerData.o: ManufacturerData.cpp StringArray.cpp trimQuotes.cpp
	$(CC) $(CFLAGS) -c ManufacturerData.cpp

StringArray.o: StringArray.cpp
	$(CC) $(CFLAGS) -c StringArray.cpp

trimQuotes.o: trimQuotes.cpp
	$(CC) $(CFLAGS) -c trimQuotes.cpp

clean:
	rm project2 *.o
