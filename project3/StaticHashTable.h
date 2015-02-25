// File: StaticHashTable.h
// Author: Matthew Leeds
// Last Edit: 2015-02-19

#pragma once
#include <fstream>
#include "MfrLinkedList.h"
#include "ManufacturerData.h"

using namespace std;

struct ManufacturerInfo;
struct UPCInfo;
class MfrLinkedList;

// Store the key in case we later search for a key that wasn't known originally
// but that collides with an actual key.
struct MfrRecord {
    ManufacturerInfo* mInfo;
    bool alias;
    unsigned int UPC;
    MfrRecord(ManufacturerInfo* inMInfo, bool inAlias, unsigned int inUPC) :
        mInfo(inMInfo), alias(inAlias), UPC(inUPC) {}
};

class StaticHashTable {

    // Since a specific hash function has to be chosen for each record,
    // we need to store the constants for that, and the actual mfr data.
    struct SecondLevelHashTable {
        unsigned int _tableSize;
        unsigned int _a;
        unsigned int _b;
        MfrRecord** MfrTable;
    };

    // Before we do the second level hashing, entries will be stored in collisions.
    // Then everything will move to noCollisions.
    struct Entry {
        MfrLinkedList* collisions;
        SecondLevelHashTable* noCollisions;
    };

    public:
        StaticHashTable() {};
        StaticHashTable(unsigned long numRecords);
        ~StaticHashTable();
        void addRecords(UPCInfo** allUPCs);
        void printHashInfo();
        ManufacturerInfo* getRecord(unsigned int key);
        void printTable();

    private:
        unsigned long _numRecords;
        unsigned long _prime;
        unsigned long _tableSize;
        unsigned long _a; // hashing function coefficient
        unsigned long _b; // hashing function coefficient
        unsigned long hashKey(unsigned long key); // primary hash function
        Entry** _allRecords;

};
