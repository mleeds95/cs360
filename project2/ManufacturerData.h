// File: ManufacturerData.h
// Author: Matthew Leeds
// Last Edit: 2015-02-06

#include <string>
#include <fstream>
#include "StringArray.h"

using namespace std;

struct Item {
    string description;
    int quantity;
    int code;
};

struct ManufacturerInfo {
    string name;
    string nameALLCAPS;
    Item** listOfItems;
    int numItems;
};

struct UPCInfo {
    int UPC;
    ManufacturerInfo* mInfo;
};

class ManufacturerData {
    public:
        ManufacturerData(ifstream& inFile);
        ~ManufacturerData();
        UPCInfo** allUPCs;
        void sortByUPCorName(bool byUPC) { mergeSort(byUPC, 0, _numUPCs - 1); }
        int getNumUPCs() { return _numUPCs; }
        friend ostream& operator<<(ostream& os, const ManufacturerData&);
        void findAliases();

    private:
        void mergeSort(bool byUPC, int start, int end);
        void merge(bool byUPC, int start, int middle, int end);
        void resizeAllUPCs();
        void resizeAliasedIndices();
        int _numUPCs;
        int _sizeAllUPCs;
        int* _aliasedIndices;
        int _numAliasedIndices;
        int _sizeAliasedIndices;
};
