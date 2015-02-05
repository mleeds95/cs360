// File: ManufacturerData.h
// Author: Matthew Leeds
// Last Edit: 2015-02-03

#include <fstream>
#include "StringArray.h"

using namespace std;

class ManufacturerData {
    public:
        ManufacturerData(ifstream& inFile);
        ~ManufacturerData() {}
        void findAliases();
        StringArray data;
        StringArray aliases;
};
