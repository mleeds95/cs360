// File: StaticHashTable.cpp
// Author: Matthew Leeds
// Last Edit: 2015-02-17

#include <fstream>

using namespace std;

class StaticHashTable {
    public:
        StaticHashTable() {};
        StaticHashTable(ifstream& inFile);
        ~StaticHashTable();

    private:
        unsigned long _numRecords;
        unsigned long _prime;
        unsigned long _tableSize;
        unsigned long _a; // hashing function coefficient
        unsigned long _b; // hashing function coefficient

};
