// File: ManufacturerData.cpp
// Author: Matthew Leeds
// Last Edit: 2015-02-24
// Purpose: Define a class for holding data for manufacturer names and UPC codes.
// Note: This class contains three data structures (array, hash table, tree),
// so it can be confusing which methods apply to which, but this way we
// can take advantage of the array's low initial cost and flexible sorting,
// and get the worst-case O(1) searches once we move to a tree/table. Since
// we're using pointers, the extra storage isn't much.

#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>
#include "ManufacturerData.h"

using namespace std;

struct MfrRecord;
void trimQuotes(string&);
bool caseInsensitiveStrcmp(const string&, const string&);
string strToUpper(string);

// Read in CSV data from a file with 6 digit codes and variable length company names.
// Stores appropriate information in a UPCInfo struct containing a ManufacturerInfo struct.
// If useRBT is true, use a Red Black Tree, otherwise use a hash table.
ManufacturerData::ManufacturerData(ifstream& inFile, bool useRBT) : 
    redBlackTree(useRBT), _numUPCs(0), _sizeAllUPCs(1),
    _allMfrCodesHT(NULL), _allMfrCodesRBT(NULL) {
    allUPCs = new UPCInfo*[1];
    string line = "";
    // Read in all the records from the file into allUPCs.
    while (getline(inFile, line)) {
        UPCInfo* thisUPC = new UPCInfo;
        thisUPC->UPC = atoi(line.substr(0,6).c_str());
        string companyName = line.substr(7);
        trimQuotes(companyName);
        ManufacturerInfo* thisMInfo = new ManufacturerInfo;
        thisMInfo->name = companyName;
        thisMInfo->nameALLCAPS = strToUpper(companyName);
        thisMInfo->numItems = 0;
        thisMInfo->sizeListOfItems = 1;
        thisMInfo->listOfItems = new Item*[1];
        thisUPC->mInfo = thisMInfo;
        thisUPC->alias = false;
        if (_numUPCs + 1 > _sizeAllUPCs)
            resizeAllUPCs();
        allUPCs[_numUPCs++] = thisUPC;
    }
}

ManufacturerData::~ManufacturerData() {
    for (unsigned long i = 0; i < _numUPCs; i++)
        delete allUPCs[i];
    delete[] allUPCs;
    if (_allMfrCodesHT != NULL) delete _allMfrCodesHT;
    if (_allMfrCodesRBT != NULL) delete _allMfrCodesRBT;
}

// Move all the data to a perfect hash table.
void ManufacturerData::toHashTable() {
    _allMfrCodesHT = new StaticHashTable(_numUPCs);
    _allMfrCodesHT->addRecords(allUPCs);
}

// Move all the data to a red-black tree.
void ManufacturerData::toRedBlackTree() {
    _allMfrCodesRBT = new RedBlackTree();
    _allMfrCodesRBT->growTree(allUPCs, _numUPCs);
}

// If you use this class as an array w/o a HashTable or RedBlackTree,
// you can use this function to free the memory properly.
void ManufacturerData::freeUPCarray() {
    for (unsigned long i = 0; i < _numUPCs; i++) {
        UPCInfo* thisUPCInfo = allUPCs[i];
        // if it's not a duplicate pointer (an alias), delete it.
        if (!thisUPCInfo->alias) {
            for (unsigned int k = 0; k < thisUPCInfo->mInfo->numItems; k++)
                delete thisUPCInfo->mInfo->listOfItems[k];
            delete[] thisUPCInfo->mInfo->listOfItems;
            delete thisUPCInfo->mInfo;
        }
    }
}

ostream& operator<<(ostream& os, const ManufacturerData& m) {
    for (unsigned long i = 0; i < m._numUPCs; i++) {
        if (m.allUPCs[i]->alias) continue;
        os << m.allUPCs[i]->UPC << endl;
        os << m.allUPCs[i]->mInfo->name << endl;
        os << "numItems: " << m.allUPCs[i]->mInfo->numItems << endl;
        for (unsigned int j = 0; j < m.allUPCs[i]->mInfo->numItems; j++) {
            os << m.allUPCs[i]->mInfo->listOfItems[j]->quantity << "x: "
               << m.allUPCs[i]->mInfo->listOfItems[j]->description << endl
               << m.allUPCs[i]->mInfo->listOfItems[j]->code << endl;
        }
        os << endl;
    }
    return os;
}

void ManufacturerData::resizeAllUPCs() {
   unsigned long newSize = _sizeAllUPCs * 2; 
   UPCInfo** newUPCs = new UPCInfo*[newSize];
   for (unsigned long i = 0; i < _numUPCs; i++) {
       newUPCs[i] = allUPCs[i];
   }
   delete[] allUPCs;
   allUPCs = newUPCs;
   _sizeAllUPCs = newSize;
}

void ManufacturerData::mergeSort(bool byUPC, unsigned long start, unsigned long end) {
    if (start < end) {
        unsigned long middle = (start + end) / 2;
        mergeSort(byUPC, start, middle);
        mergeSort(byUPC, middle + 1, end);
        merge(byUPC, start, middle, end);
    }
}

// This merges two sorted subarrays of allUPCs (either on UPC or ALL CAPS name).
void ManufacturerData::merge(bool byUPC, unsigned long start, unsigned long middle, unsigned long end) {
    unsigned long arr1Length = middle - start + 1;
    unsigned long arr2Length = end - middle;
    UPCInfo* arr1[arr1Length];
    UPCInfo* arr2[arr2Length];
    unsigned long i;
    for (i = start; i <= middle; i++) {
        arr1[i - start] = allUPCs[i];
    }
    unsigned long j;
    for (j = middle + 1; j <= end; j++) {
        arr2[j - middle - 1] = allUPCs[j];
    }
    unsigned long l = 0; // arr1 counter
    unsigned long m = 0; // arr2 counter
    // Now merge them by copying an element from one or the other each iteration.
    unsigned long k; // arr counter
    for (k = start; k <= end; k++) {
        if (l >= arr1Length) {
            allUPCs[k] = arr2[m];
            m++;
        } else if (m >= arr2Length) {
            allUPCs[k] = arr1[l];
            l++;
        } else if (( byUPC && (arr1[l]->UPC                <= arr2[m]->UPC               )) || 
                   (!byUPC && (arr1[l]->mInfo->nameALLCAPS <= arr2[m]->mInfo->nameALLCAPS))) {
            allUPCs[k] = arr1[l];
            l++;
        } else {
            allUPCs[k] = arr2[m];
            m++;
        }
    }
}

// This finds instances in allUPCs where the same company has multiple UPC codes,
// and points them all to the same UPCInfo struct. It assumes that this is run
// before listOfItems has been initialized (it makes no attempt to free that memory).
void ManufacturerData::findAliases() {
    // First sort them by name.
    sortByUPCorName(false);
    // Walk through the array looking for matching company names.
    if (_numUPCs < 2) return;
    for (unsigned long i = 1; i < _numUPCs; i++) {
        ManufacturerInfo* lastEntry = allUPCs[i-1]->mInfo;
        if (allUPCs[i]->mInfo->nameALLCAPS == lastEntry->nameALLCAPS) {
            // Have each matching entry point to the first match.
            delete[] allUPCs[i]->mInfo->listOfItems;
            delete allUPCs[i]->mInfo;
            allUPCs[i]->mInfo = lastEntry;
            allUPCs[i]->alias = true;
        }
    }
}

// This finds the ManufacturerInfo* for a given UPC, either in the Hash Table or Red-Black Tree.
ManufacturerInfo* ManufacturerData::findByUPC(unsigned int searchUPC) {
    if (redBlackTree)
        return _allMfrCodesRBT->getMInfo(searchUPC);
    else
        return _allMfrCodesHT->getRecord(searchUPC);
}

// This takes the first 6 digits of the UPC as inUPC, all 12 digits as inCode,
// and the item description as inDescription. It adds the item in the appropriate 
// manufacturer's object or increments the quantity for pre-existing items.
bool ManufacturerData::addItem(unsigned int inUPC, unsigned long inCode, string inDescription) {
    ManufacturerInfo* match = findByUPC(inUPC); 
    if (match == NULL) 
        return false;
    // If the item is already there, increment its quantity.
    // Since n is relatively small, this is faster than sorting it first.
    // I verified this empirically.
    for (unsigned int j = 0; j < match->numItems; j++) {
        if (match->listOfItems[j]->description == inDescription) {
            match->listOfItems[j]->quantity++;
            return true;
        }
    }
    // At this point we know this is an item we haven't seen before.
    // Resize listOfItems if necessary
    if (match->numItems + 1 > match->sizeListOfItems) {
        unsigned int newSize = match->sizeListOfItems * 2;
        Item** newListOfItems = new Item*[newSize];
        for (unsigned int i = 0; i < match->numItems; i++)
            newListOfItems[i] = match->listOfItems[i];
        delete[] match->listOfItems;
        match->listOfItems = newListOfItems;
        match->sizeListOfItems = newSize;
    }
    // Add a new item.
    Item* newItem = new Item;
    newItem->quantity = 1;
    newItem->code = inCode;
    newItem->description =  inDescription;
    match->listOfItems[match->numItems++] = newItem;
    return true;
}

// This prints of report of all items sold under their respective manufacturers,
// which are alhabetically sorted. The format is:
// <MANUFACTURER NAME>
// Qty <X> - <description>
// ...
//
void ManufacturerData::printReport() {
    sortByUPCorName(false);
    for (unsigned long i = 0; i < _numUPCs; i++) {
        // Don't print out duplicate entries.
        if (allUPCs[i]->alias) continue;
        // Of course it would be more efficient just to use the array,
        // but this way we're using the appropriate data structure.
        ManufacturerInfo* thisM = findByUPC(allUPCs[i]->UPC);
        cout << thisM->name << endl;
        for (unsigned int k = 0; k < thisM->numItems; k++) {
            cout << "Qty " << thisM->listOfItems[k]->quantity << " - ";
            cout << thisM->listOfItems[k]->description << endl;
        }
        cout << endl << endl;
    }
}
