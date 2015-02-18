// File: StaticHashTable.cpp
// Author: Matthew Leeds
// Last Edit: 2015-02-17

#include <iostream>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include "ManufacturerData.h"
#include "StaticHashTable.h"

using namespace std;

unsigned long StaticHashTable::hashKey(unsigned long key) {
    return (((_a * key + _b) % _prime) % _tableSize);
}

// This constructs a perfect hash table (worst case constant access) by doing two passes
// over the data, one for each level of hashing.
StaticHashTable::StaticHashTable(unsigned long numRecords) :
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
    _a = ((unsigned long)pow(rand(), 2)) % _prime;
    srand(time(NULL) / 2);
    _b = ((unsigned long)pow(rand(), 2)) % _prime;
}

StaticHashTable::~StaticHashTable() {}

void StaticHashTable::printHashInfo() {
    cout << "_numRecords " << _numRecords << endl;
    cout << "_prime " << _prime << endl;
    cout << "_tableSize " << _tableSize << endl;
    cout << "_a " << _a << endl;
    cout << "_b " << _b << endl;  
}

// This takes an array with all the manufacturers' info and converts it
// to a hash table. Aliases have already been corrected at this point.
void StaticHashTable::addRecords(UPCInfo** allUPCs) {
    allRecords = new Entry*[_tableSize](); 
    // First run all the records through the primary hash function.
    for (unsigned long i = 0; i < _numRecords; i++) {
        unsigned long h = hashKey(allUPCs[i]->UPC);
        if (allRecords[h] == NULL) {
            Entry* thisEntry = new Entry();
            thisEntry->collisions = new MfrLinkedList();
            thisEntry->collisions->addValue(allUPCs[i]->mInfo, allUPCs[i]->alias);
            allRecords[h] = thisEntry;
        } else {
            allRecords[h]->collisions->addValue(allUPCs[i]->mInfo, allUPCs[i]->alias);
        }
    }
    // Now find secondary hash functions for each entry,
    // such that there are no collisions on this level.
    //TODO
    /*for (unsigned long i = 0; i < _tableSize; i++) {
        if (allRecords[i] != NULL) {
            cout << i << allRecords[i]->collisions->head->mInfo->name << endl;
            Node* thisNode = allRecords[i]->collisions->head;
            while (thisNode->next != NULL) {
                cout << "  " << thisNode->next->mInfo->name << endl;
                thisNode = thisNode->next;
            }
        }
    }
    printHashInfo();*/
}
