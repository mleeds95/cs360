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
        long fullCode = atol(line.substr(0,12).c_str());
        string restOfLine = line.substr(13);
        // Sometimes there are commas in the second field that are escaped.
        bool escaped = false; // are we in between double quotes?
        size_t pos = 0;
        size_t found = string::npos;
        found = restOfLine.find("\"\"", pos);
        while(found != string::npos) {
            escaped = !escaped;
            pos = found + 2;
            // If the next double quotes are in the next field and we've found an even number, break
            if (!escaped && restOfLine.find(',', pos) < restOfLine.find("\"\"", pos))
                break;
            found = restOfLine.find("\"\"", pos);
        }
        pos = restOfLine.find(',', pos);
        if (pos == string::npos) {
            numFailure++;
            continue;
        }
        string description = restOfLine.substr(pos + 1);
        trimQuotes(description);
        if (mData.addItem(UPC, fullCode, description))
            numSuccess++;
        else
            numFailure++;
    }
    //cout << "numSuccess = " << numSuccess << endl;
    //cout << "numFailure = " << numFailure << endl;
}
