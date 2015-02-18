// File: main.cpp
// Author: Matthew Leeds
// Last Edit: 2015-02-17
// Purpose: For CS 360, Project 3: adding hash maps and trees to Project 2.

#include <iostream>
#include <string.h>
#include "SalesData.h"

using namespace std;

const char* MANUFACTURERS_FILENAME = "mcodes.csv";
const char* SALES_FILENAME = "sales.csv";

int main(int argc, char* argv[]) {
    // determine if we should use a red-black tree rather than a hash table
    bool useRBT = false;
    if (argc > 1 && !strcmp(argv[1], "-b"))
        useRBT = true;
    // Read in Manufacturer data from the disk.
    ifstream manufacturersFile(MANUFACTURERS_FILENAME);
    if (!manufacturersFile.is_open()) {
        cerr << "Error: " << MANUFACTURERS_FILENAME << " file inaccessible or non-existent!" << endl;
        return 1;
    }
    // Initialize manufacturers data object.
    ManufacturerData mData = ManufacturerData(manufacturersFile);
    manufacturersFile.close();
    // Find instances where companies have multiple codes, and redirect those pointers.
    mData.findAliases();
    // Convert to Hash Table or RBT
    if (useRBT)
        cout << "TODO: RBT" << endl;
    else
        mData.toHashTable();
    /*
    // Read in Sales data from the disk.
    ifstream salesFile(SALES_FILENAME);
    if (!salesFile.is_open()) {
        cerr << "Error: " << SALES_FILENAME << " file inaccessible or non-existent!" << endl;
        return 1;
    }
    // Initialize sales data object (which will add items to the manufacturers as it goes).
    SalesData sData = SalesData(salesFile, mData);
    salesFile.close();
    // Output a nicely formatted sales report.
    cout << mData << endl;
    mData.printReport();
    */
    return 0;
}
