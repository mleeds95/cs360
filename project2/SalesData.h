// File: SalesData.h
// Author: Matthew Leeds
// Last Edit: 2015-02-08

#include <fstream>
#include "ManufacturerData.h"

using namespace std;

class SalesData {
    public:
        SalesData(ifstream& inFile, ManufacturerData& mData);
        ~SalesData() {}
};
