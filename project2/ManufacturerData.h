// File: ManufacturerData.h
// Author: Matthew Leeds
// Last Edit: 2015-02-02

#include <fstream>
#include <string>
#include "StringData.h"

using namespace std;

class ManufacturerData: public StringData {
    public:
        ManufacturerData(ifstream& inFile);
        ~ManufacturerData();
        void findAliases();

    private:
        string** _aliases;
};
