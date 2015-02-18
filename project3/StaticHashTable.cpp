// File: StaticHashTable.cpp
// Author: Matthew Leeds
// Last Edit: 2015-02-17

#include "StaticHashTable.h"

StaticHashTable::StaticHashTable(ifstream& inFile) {
    inFile.seekg(0, inFile.end);
    int fileLength = inFile.tellg();
    int maxRecords = fileLength / 8;
    // Hardcode the prime for efficiency. This number is greater than any key could be.
    unsigned int prime = 1572869;
    // list of primes that are roughly between powers of two, 
    // thanks to http://planetmath.org/goodhashtableprimes
    // Of course we could calculate these but it would take much longer.
    int specialPrimes[] = {53, 97, 193, 389, 769, 1543, 3079, 6151, 12289, 24593, 49157, 98317,
                           196613, 393241, 786433, 1572869, 3145739, 6291469, 12582917, 25165843,
                           50331653, 100663319, 201326611, 402653189, 805306457, 1610612741};
    inFile.seekg(0, inFile.beg);
}

StaticHashTable::~StaticHashTable() {}
