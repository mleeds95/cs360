// File: ManufacturerData.cpp
// Author: Matthew Leeds
// Last Edit: 2015-02-02
// Purpose: Define a class for holding data for manufacturer names and UPC codes.

#include "ManufacturerData.h"
#include <string>

using namespace std;

// Read in CSV data from a file with 6 digit codes and variable length company names.
ManufacturerData::ManufacturerData(ifstream& inFile) {
    _arrSize = 2;
    _arr = new string*[_arrSize];
    _numFilled = 0;
    string line = "";
    // Read in all the records from the file into _arr, resizing when necessary.
    while (getline(inFile, line)) {
        _arr[_numFilled++] = new string(line.substr(0,6)); // UPC code
        string companyName = line.substr(7);
        trimQuotes(companyName);
        _arr[_numFilled++] = new string(companyName);
        if (_numFilled == _arrSize)
            resizeArray(true); // makes the array twice as big
    }
    resizeArray(false);
}

ManufacturerData::~ManufacturerData() {
    for (int i = 0; i < this->_arrSize; i++) {
        delete this->_arr[i];
    }
}

// This finds instances in _arr where the same company has multiple UPC codes,
// and stores them in _aliases as ["company_name","# aliases","alias1","alias2",...]
void ManufacturerData::findAliases() {
    sortEvensOrOdds(false); // sort by company name
    //TODO implement
}
