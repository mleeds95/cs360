// File: StaticHashTable.cpp
// Author: Matthew Leeds
// Last Edit: 2015-02-19

#include <iostream>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include "ManufacturerData.h"
#include "StaticHashTable.h"

using namespace std;

// Calculate the primary hash function for a given key value.
unsigned long StaticHashTable::hashKey(unsigned long key) {
    return (((_a * key + _b) % _prime) % _tableSize);
}

// This sets up the paramaters for our hash table (prime, a, b, tableSize, numRecords).
StaticHashTable::StaticHashTable(unsigned long numRecords) :
    _numRecords(numRecords) {
    // This is a list of primes that are roughly between powers of two, 
    // thanks to http://planetmath.org/goodhashtableprimes
    // Of course we could calculate these but it would take much longer.
    unsigned long specialPrimes[26] = {53, 97, 193, 389, 769, 1543, 3079, 6151, 12289, 24593, 49157, 98317,
                                       196613, 393241, 786433, 1572869, 3145739, 6291469, 12582917, 25165843,
                                       50331653, 100663319, 201326611, 402653189, 805306457, 1610612741};
    if (numRecords > specialPrimes[25]) {
        _tableSize = numRecords * 1.5;
    } else {
        for (int i = 0; i < 26; i++) {
            // Find a suitable size that keeps the load factor <= 0.75.
            if (specialPrimes[i] > (unsigned long)(numRecords * 1.5)) {
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
    _b = ((unsigned long)pow(rand(), 2)) % _prime;
    _allRecords = new Entry*[_tableSize];
    for (unsigned long i = 0; i < _tableSize; i++)
        _allRecords[i] = NULL;
}

StaticHashTable::~StaticHashTable() {
    for (unsigned long i = 0; i < _tableSize; i++) {
        if (_allRecords[i] != NULL) {
            // free noCollisions memory
            MfrRecord** thisMfrTable = _allRecords[i]->noCollisions->MfrTable;
            for (unsigned int j = 0; j < _allRecords[i]->noCollisions->_tableSize; j++) {
                if (thisMfrTable[j] != NULL) { 
                    if (!thisMfrTable[j]->alias) {
                        for (unsigned int k = 0; k < thisMfrTable[j]->mInfo->numItems; k++)
                            delete thisMfrTable[j]->mInfo->listOfItems[k];
                        delete[] thisMfrTable[j]->mInfo->listOfItems;
                        delete thisMfrTable[j]->mInfo;
                    }
                    delete thisMfrTable[j];
                }
            }
            delete[] thisMfrTable;
            delete _allRecords[i]->noCollisions;
            // free collisions memory
            MfrLinkedList* thisMfrList = _allRecords[i]->collisions;
            LLNode* n = thisMfrList->head;
            while (n != NULL) {
                thisMfrList->head = thisMfrList->head->next;
                delete n;
                n = thisMfrList->head;
            }
            delete _allRecords[i]->collisions;
            // free the Entry itself
            delete _allRecords[i];
        }
    }
    delete[] _allRecords;
}

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
    // First run all the records through the primary hash function.
    for (unsigned long i = 0; i < _numRecords; i++) {
        unsigned long h = hashKey(allUPCs[i]->UPC);
        if (_allRecords[h] == NULL) {
            Entry* thisEntry = new Entry();
            thisEntry->collisions = new MfrLinkedList();
            thisEntry->collisions->addValue(allUPCs[i]->mInfo, allUPCs[i]->alias, allUPCs[i]->UPC);
            _allRecords[h] = thisEntry;
        } else {
            _allRecords[h]->collisions->addValue(allUPCs[i]->mInfo, allUPCs[i]->alias, allUPCs[i]->UPC);
        }
    }
    // Now find secondary hash functions for each entry that don't collisions.
    // Move all the data from the MfrLinkedList* to the SecondLevelHashTable* in the process.
    for (unsigned long i = 0; i < _tableSize; i++) {
        if (_allRecords[i] != NULL) {
            MfrLinkedList* theCollisions = _allRecords[i]->collisions;
            SecondLevelHashTable* thisTable = new SecondLevelHashTable();
            if (theCollisions->numItems == 1) {
                thisTable->_tableSize = 1;
                thisTable->_a = 0;
                thisTable->_b = 0;
                thisTable->MfrTable = new MfrRecord*[1];
                thisTable->MfrTable[0] = new MfrRecord(theCollisions->head->mInfo, theCollisions->head->alias);
            } else {
                thisTable->_tableSize = (unsigned int)pow(theCollisions->numItems, 2);
                thisTable->MfrTable = new MfrRecord*[thisTable->_tableSize]();
                // Now we need to keep trying random combinations of a and b until we find one
                // that doesn't have any collisions.
                bool collisionFree = false;
                while (!collisionFree) {
                    for (unsigned int j = 0; j < thisTable->_tableSize; j++) {
                        if (thisTable->MfrTable[j] != NULL) {
                            delete thisTable->MfrTable[j];
                            thisTable->MfrTable[j] = NULL;
                        }
                    }
                    collisionFree = true; // unless proven otherwise
                    thisTable->_a = rand() % _prime;
                    thisTable->_b = rand() % _prime;
                    LLNode* thisNode = theCollisions->head;
                    for (unsigned int k = 0; k < theCollisions->numItems; k++) {
                        unsigned int h = (((thisTable->_a * thisNode->UPC + thisTable->_b) % _prime) % thisTable->_tableSize);
                        if (thisTable->MfrTable[h] != NULL) {
                            collisionFree = false;
                            break;
                        } else {
                            thisTable->MfrTable[h] = new MfrRecord(thisNode->mInfo, thisNode->alias);
                        }
                        thisNode = thisNode->next;
                    } 
                }
            }
            // Assign our new SecondLevelHashTable* to the current slot.
            _allRecords[i]->noCollisions = thisTable;
        }
    }
    //printHashInfo();
}

MfrRecord* StaticHashTable::getRecord(unsigned int key) {
    unsigned long h1 = hashKey(key);
    if (_allRecords[h1] != NULL) {
        SecondLevelHashTable* secondaryTable = _allRecords[h1]->noCollisions;
        unsigned int h2 = (((secondaryTable->_a * key + secondaryTable->_b) % _prime) % secondaryTable->_tableSize);
        if (secondaryTable->MfrTable[h2] != NULL)
            return secondaryTable->MfrTable[h2];
    }
    return NULL;
}
