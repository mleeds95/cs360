// File: ManufacturerData.cpp
// Author: Matthew Leeds
// Last Edit: 2015-02-04
// Purpose: Define a class for holding data for manufacturer names and UPC codes.

#include <iostream>
#include <string>
#include <sstream>
#include "ManufacturerData.h"

using namespace std;

void trimQuotes(string& s);

// Read in CSV data from a file with 6 digit codes and variable length company names.
ManufacturerData::ManufacturerData(ifstream& inFile) : data(2), aliases(4) {
    string line = "";
    // Read in all the records from the file into data.
    while (getline(inFile, line)) {
        data.append(new string(line.substr(0,6))); // UPC code
        string companyName = line.substr(7);
        trimQuotes(companyName);
        data.append(new string(companyName));
    }
    data.resizeArray(false);
}

// This finds instances in _arr where the same company has multiple UPC codes,
// and stores them in aliases as ["company_name","# aliases","alias1","alias2",...]
void ManufacturerData::findAliases() {
    data.sortEvensOrOdds(false); // sort by company name
    cout << data << endl;
    int matches = 1;
    // Walk through the data array looking for matching company names.
    if (data.getSize() > 2) {
        for (int i = 3; i < data.getSize(); i += 2) {
           if (*data[i] == *data[i-2]) matches++;
           else {
               // If the previous ones were matches, record this company's aliases.
               if (matches > 1 || (i == data.getSize() - 1 && matches > 1)) {
                   aliases.append(new string(*data[i-2]));
                   ostringstream oss;
                   oss << matches;
                   aliases.append(new string(oss.str()));
                   for (int j = 1; j <= matches; j++) 
                       aliases.append(new string(*data[i-1-(j*2)]));
               }
               // Reset the counter (everything is a match to itself).
               matches = 1;
           } 
        }
        aliases.resizeArray(false);
    }
}
