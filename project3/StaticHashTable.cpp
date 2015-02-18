// File: StaticHashTable.cpp
// Author: Matthew Leeds
// Last Edit: 2015-02-17

#include <iostream>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include "StaticHashTable.h"
#include "MfrLinkedList.h"
#include "ManufacturerData.h"

using namespace std;

unsigned long hashKey(unsigned long key) {
    return (((_a * key + _b) % _prime) % _tableSize);
}

// This constructs a perfect hash table (worst case constant access) by doing two passes
// over the data, one for each level of hashing.
StaticHashTable::StaticHashTable(unsigned int numRecords) 
    _numRecords(numRecords) {
    // This is a list of primes that are roughly between powers of two, 
    // thanks to http://planetmath.org/goodhashtableprimes
    // Of course we could calculate these but it would take much longer.
    unsigned long specialPrimes[26] = {53, 97, 193, 389, 769, 1543, 3079, 6151, 12289, 24593, 49157, 98317,
                                       196613, 393241, 786433, 1572869, 3145739, 6291469, 12582917, 25165843,
                                       50331653, 100663319, 201326611, 402653189, 805306457, 1610612741};
    if (numRecords > specialPrimes[25]) {
        _tableSize = numRecords;
    } else {
        for (int i = 0; i < 26; i++) {
            if (specialPrimes[i] > numRecords) {
                _tableSize = specialPrimes[i];
                break;
            }
        }
    }
    // Hardcode the prime for efficiency. This number is greater than any key could be.
    _prime = 1000003;
    // Choose a and b, two constants between 1 and _prime - 1
    // Assume RAND_MAX is at least 2^31, so RAND_MAX^2 is near numeric_limits<unsigned long>::max()
    srand(time(NULL));
    _a = pow(rand(), 2) % _prime;
    srand(time(NULL) / 2);
    _b = pow(rand(), 2) % _prime;
}

StaticHashTable::~StaticHashTable() {}

// This takes an array with all the manufacturers' info and converts it
// to a hash table. Aliases have already been corrected at this point.
void StaticHashTable::addRecords(UPCInfo** allUPCs, unsigned long length) {
   for (unsigned long i = 0; i < length; i++) {
        unsigned long h = hashKey(allUPCs[i]->UPC);
        if //TODO
   }
}

