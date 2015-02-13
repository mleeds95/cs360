// File: ManufacturerData.cpp
// Author: Matthew Leeds
// Last Edit: 2015-02-08
// Purpose: Define a class for holding data for manufacturer names and UPC codes.

#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>
#include "ManufacturerData.h"

using namespace std;

void trimQuotes(string&);
bool caseInsensitiveStrcmp(const string&, const string&);
string strToUpper(string);

// Read in CSV data from a file with 6 digit codes and variable length company names.
// Stores appropriate information in a UPCInfo struct containing a ManufacturerInfo struct.
ManufacturerData::ManufacturerData(ifstream& inFile) : 
    _numUPCs(0), _sizeAllUPCs(1) {
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
    for (int i = 0; i < _numUPCs; i++) {
        UPCInfo* thisUPCInfo = allUPCs[i];
        // if it's not a duplicate pointer (an alias), delete it.
        if (!thisUPCInfo->alias) {
            for (int k = 0; k < thisUPCInfo->mInfo->numItems; k++)
                delete thisUPCInfo->mInfo->listOfItems[k];
            delete[] thisUPCInfo->mInfo->listOfItems;
            delete thisUPCInfo->mInfo;
        }
        delete thisUPCInfo;
    }
    delete[] allUPCs;
}

ostream& operator<<(ostream& os, const ManufacturerData& m) {
    for (int i = 0; i < m._numUPCs; i++) {
        if (m.allUPCs[i]->alias) continue;
        os << m.allUPCs[i]->UPC << endl;
        os << m.allUPCs[i]->mInfo->name << endl;
        os << "numItems: " << m.allUPCs[i]->mInfo->numItems << endl;
        for (int j = 0; j < m.allUPCs[i]->mInfo->numItems; j++) {
            os << m.allUPCs[i]->mInfo->listOfItems[j]->quantity << "x: "
               << m.allUPCs[i]->mInfo->listOfItems[j]->description << endl
               << m.allUPCs[i]->mInfo->listOfItems[j]->code << endl;
        }
        os << endl;
    }
    return os;
}

void ManufacturerData::resizeAllUPCs() {
   int newSize = _sizeAllUPCs * 2; 
   UPCInfo** newUPCs = new UPCInfo*[newSize];
   for (int i = 0; i < _numUPCs; i++) {
       newUPCs[i] = allUPCs[i];
   }
   delete[] allUPCs;
   allUPCs = newUPCs;
   _sizeAllUPCs = newSize;
}

void ManufacturerData::mergeSort(bool byUPC, int start, int end) {
    if (start < end) {
        int middle = (start + end) / 2;
        mergeSort(byUPC, start, middle);
        mergeSort(byUPC, middle + 1, end);
        merge(byUPC, start, middle, end);
    }
}

// This merges two sorted subarrays of allUPCs (either on UPC or ALL CAPS name).
void ManufacturerData::merge(bool byUPC, int start, int middle, int end) {
    int arr1Length = middle - start + 1;
    int arr2Length = end - middle;
    UPCInfo* arr1[arr1Length];
    UPCInfo* arr2[arr2Length];
    int i;
    for (i = start; i <= middle; i++) {
        arr1[i - start] = allUPCs[i];
    }
    int j;
    for (j = middle + 1; j <= end; j++) {
        arr2[j - middle - 1] = allUPCs[j];
    }
    int l = 0; // arr1 counter
    int m = 0; // arr2 counter
    // Now merge them by copying an element from one or the other each iteration.
    int k; // arr counter
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
    for (int i = 1; i < _numUPCs; i++) {
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

// This assumes allUPCs is sorted by UPC and does a binary search to find a 
// given manufacturer by UPC, returning a pointer to its ManufacturerInfo object.
ManufacturerInfo* ManufacturerData::findByUPC(int searchUPC, int start, int end) {
    ManufacturerInfo* rightResult = NULL;
    ManufacturerInfo* leftResult = NULL;
    int middle = (start + end) / 2;
    if (allUPCs[middle]->UPC == searchUPC)
        return allUPCs[middle]->mInfo;
    if (start < end) {
        if (allUPCs[middle]->UPC < searchUPC)
            rightResult = findByUPC(searchUPC, middle + 1, end);
        else
            leftResult = findByUPC(searchUPC, start, middle - 1);
    }
    if (rightResult != NULL) 
        return rightResult;
    if (leftResult != NULL) 
        return leftResult;
    return NULL;
}

// This takes the first 6 digits of the UPC as inUPC, all 12 digits as inCode,
// and the item description as inDescription. It adds the item in the appropriate 
// manufacturer's object or increments the quantity for pre-existing items.
bool ManufacturerData::addItem(int inUPC, long inCode, string inDescription) {
    ManufacturerInfo* match = findByUPC(inUPC, 0, _numUPCs - 1); 
    if (match == NULL) 
        return false;
    // If the item is already there, increment its quantity.
    // Since n is relatively small, this is faster than sorting it first.
    // I verified this empirically.
    for (int j = 0; j < match->numItems; j++) {
        if (match->listOfItems[j]->description == inDescription) {
            match->listOfItems[j]->quantity++;
            return true;
        }
    }
    // At this point we know this is an item we haven't seen before.
    // Resize listOfItems if necessary
    if (match->numItems + 1 > match->sizeListOfItems) {
        int newSize = match->sizeListOfItems * 2;
        Item** newListOfItems = new Item*[newSize];
        for (int i = 0; i < match->numItems; i++)
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
    for (int i = 0; i < _numUPCs; i++) {
        // Don't print out duplicate entries.
        if (allUPCs[i]->alias) continue;
        ManufacturerInfo* thisM = allUPCs[i]->mInfo;
        cout << thisM->name << endl;
        for (int k = 0; k < thisM->numItems; k++) {
            cout << "Qty " << thisM->listOfItems[k]->quantity << " - ";
            cout << thisM->listOfItems[k]->description << endl;
        }
        cout << endl << endl;
    }
}
