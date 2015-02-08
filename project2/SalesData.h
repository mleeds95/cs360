// File: SalesData.h
// Author: Matthew Leeds
// Last Edit: 2015-02-05

#include <fstream>

using namespace std;

class SalesData {
    public:
        SalesData(ifstream& inFile);
        ~SalesData() {}
        StringArray data;
}
