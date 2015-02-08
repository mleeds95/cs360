// File: main.cpp
// Author: Matthew Leeds
// Last Edit: 2015-02-08
// Purpose: For CS 360, Project 2: reading and processing sales data in CSV format.

#include <iostream>
#include "SalesData.h"

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
    // Find instances where companies have multiple codes, and redirect those pointers.
    mData.findAliases();
    // Sort by UPC so we can do binary searches when we're adding items.
    mData.sortByUPCorName(true);
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
    mData.printReport();
    return 0;
}
