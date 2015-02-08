// File: SalesData.cpp
// Author: Matthew Leeds
// Last Edit: 2015-02-08

#include <string>
#include <iostream>
#include <cstdlib>
#include "SalesData.h"

using namespace std;

void trimQuotes(string&);

SalesData::SalesData(ifstream& inFile, ManufacturerData& mData) {
    // Read in all the records, adding each to its ManufacturerInfo object.
    string line = "";
    unsigned int numSuccess = 0;
    unsigned int numFailure = 0;
    while (getline(inFile, line)) {
        if (line.length() < 16) {
            numFailure++;
            continue;
        }
        // Assume if the line is long enough, it's formatted roughly correctly.
        int UPC = atoi(line.substr(0,6).c_str());
        int fullCode = atoi(line.substr(0,12).c_str());
        string restOfLine = line.substr(13);
        size_t nextComma = restOfLine.find(',');
        if (nextComma == string::npos) {
            numFailure++;
            continue;
        }
        string description = restOfLine.substr(nextComma + 1);
        trimQuotes(description);
        if (mData.addItem(UPC, fullCode, description))
            numSuccess++;
        else
            numFailure++;
    }
    cout << "numSuccess = " << numSuccess << endl;
    cout << "numFailure = " << numFailure << endl;
} 
