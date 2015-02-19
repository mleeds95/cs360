// File: ManufacturerData.h
// Author: Matthew Leeds
// Last Edit: 2015-02-19

#pragma once
#include <string>
#include <fstream>
#include "StaticHashTable.h"

using namespace std;

struct Item {
    string description;
    unsigned int quantity;
    unsigned long code;
};

struct ManufacturerInfo {
    string name;
    string nameALLCAPS;
    Item** listOfItems;
    unsigned int numItems;
    unsigned int sizeListOfItems;
};

struct UPCInfo {
    unsigned int UPC;
    ManufacturerInfo* mInfo;
    bool alias;
};

class ManufacturerData {
    public:
        ManufacturerData(ifstream& inFile, bool useRBT);
        ~ManufacturerData();
        UPCInfo** allUPCs;
        void sortByUPCorName(bool byUPC) { mergeSort(byUPC, 0, _numUPCs - 1); }
        int getNumUPCs() { return _numUPCs; }
        ManufacturerInfo* findByUPC(unsigned int UPC, unsigned long start, unsigned long end);
        bool addItem(unsigned int UPC, unsigned long fullCode, string description);
        friend ostream& operator<<(ostream& os, const ManufacturerData&);
        void findAliases();
        void printReport();
        void toHashTable();
        void freeUPCarray();
        bool redBlackTree;

    private:
        void mergeSort(bool byUPC, unsigned long start, unsigned long end);
        void merge(bool byUPC, unsigned long start, unsigned long middle, unsigned long end);
        void resizeAllUPCs();
        unsigned long _numUPCs;
        unsigned long _sizeAllUPCs;
        StaticHashTable* _allMfrCodes;
};
