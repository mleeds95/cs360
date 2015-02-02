// File: ManufacturerData.cpp
// Author: Matthew Leeds
// Last Edit: 2015-02-01
// Purpose: Define a class for holding data for manufacturer names and UPC codes.

#include "ManufacturerData.h"
#include <sstream>
#include <iostream>
#include <string>

using namespace std;

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
    // sort by name
    // check for duplicates
}

ManufacturerData::~ManufacturerData() {
    for (int i = 0; i < this->_arrSize; i++) {
        delete this->_arr[i];
    }
}
