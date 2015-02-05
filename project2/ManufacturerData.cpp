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
ManufacturerData::ManufacturerData(ifstream& inFile) {
    data = StringArray(2);
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
// and stores them in _aliases as ["company_name","# aliases","alias1","alias2",...]
void ManufacturerData::findAliases() {
    data.sortEvensOrOdds(false); // sort by company name
    aliases = StringArray(4);
    int matches = 0;
    string lastName = "";
    if (data.getSize() >= 2) lastName = *data[1];
    for (int i = 3; i < data.getSize(); i += 2) {
       if (*data[i] == lastName) matches++;
       else if (matches > 0) {
           // Add this company's aliases.
           aliases.append(new string(lastName));
           ostringstream oss;
           oss << matches;
           aliases.append(new string(oss.str()));
           for (int j = 0; j < matches; j++) 
               aliases.append(new string(*data[i-1-j]));
           matches = 0;
       }
    }
    aliases.resizeArray(false);
    cout << "found some aliases" << endl;
    cout << aliases << endl;
}
