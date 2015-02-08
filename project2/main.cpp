// File: main.cpp
// Author: Matthew Leeds
// Last Edit: 2015-02-02
// Purpose: For CS 360, Project 2: reading and processing sales data in CSV format.

#include <iostream>
#include <fstream>
#include "ManufacturerData.h"

using namespace std;

const char* MANUFACTURERS_FILENAME = "mfrs.csv";
const char* SALES_FILENAME = "items.csv";

int main() {
    // Read in Manufacturer data from the disk.
    ifstream manufacturersFile(MANUFACTURERS_FILENAME);
    if (!manufacturersFile.is_open()) {
        cerr << "Error: " << MANUFACTURERS_FILENAME << " file inaccessible or non-existent!" << endl;
        return 1;
    }
    // Initialize manufacturers data object.
    ManufacturerData mData = ManufacturerData(manufacturersFile);
    manufacturersFile.close();
    mData.findAliases();
    mData.sortByUPCorName(true);
    // ManufacturerInfo* result = mData.findByUPC(200, 0, mData.getNumUPCs() - 1);
    // cout << result->name << endl;
    /* Read in Sales data from the disk.
    ifstream salesFile(SALES_FILENAME);
    if (!salesFile.is_open()) {
        cerr << "Error: " << SALES_FILENAME << " file inaccessible or non-existent!" << endl;
        return 1;
    }
    // initialize sales data object
    salesFile.close();
    // Output ish.*/
    return 0;
}
