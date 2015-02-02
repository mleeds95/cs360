// File: ManufacturerData.cpp
// Author: Matthew Leeds
// Last Edit: 2015-02-01
// Purpose: Define a class for holding data for manufacturer names and UPC codes.

#include "ManufacturerData.h"
#include <sstream>
#include <iostream>
#include <string>

using namespace std;

void trimQuotes(string&);

// Read in CSV data from a file with 6 digit codes and variable length company names.
ManufacturerData::ManufacturerData(ifstream& inFile) {
    this->_arrSize = 2;
    this->_arr = new string*[this->_arrSize];
    this->_numFilled = 0;
    string line = "";
    // Read in all the records from the file into _arr, resizing when necessary.
    while (getline(inFile, line)) {
        this->_arr[this->_numFilled++] = new string(line.substr(0,6)); // UPC code
        string companyName = line.substr(7);
        trimQuotes(companyName);
        this->_arr[this->_numFilled++] = new string(companyName);
        if (this->_numFilled == this->_arrSize)
            this->resizeArray(true); // makes the array twice as big
    }
    this->resizeArray(false);
}

ManufacturerData::~ManufacturerData() {
    for (int i = 0; i < this->_arrSize; i++) {
        delete this->_arr[i];
    }
}

// This resizes _arr to twice as big or down to the space that's actually used,
// depending on the 'bigger' parameter.
void ManufacturerData::resizeArray(bool bigger) {
    int newSize;
    if (bigger)
        newSize = this->_arrSize * 2;
    else
        newSize = this->_numFilled;
    if (newSize != this->_arrSize) {
        string** largerArr = new string*[newSize];
        for (int i = 0; i < this->_numFilled; i++) {
            largerArr[i] = this->_arr[i];
        }
        delete this->_arr;
        this->_arr = largerArr;
        this->_arrSize = newSize;
    }
}

ostream& operator<<(ostream& os, const ManufacturerData& m) {
    for (int i = 0; i < m._arrSize; i++) {
        os << *m._arr[i] << endl;
    }
    return os;
}

void ManufacturerData::sortByCode() {
    //TODO
}

void ManufacturerData::sortByName() {
    //TODO
}
