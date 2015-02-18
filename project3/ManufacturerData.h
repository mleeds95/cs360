// File: ManufacturerData.h
// Author: Matthew Leeds
// Last Edit: 2015-02-17

#include <string>
#include <fstream>
#include "StaticHashTable.h"

using namespace std;

struct Item {
    string description;
    int quantity;
    long code;
};

struct ManufacturerInfo {
    string name;
    string nameALLCAPS;
    Item** listOfItems;
    int numItems;
    int sizeListOfItems;
};

struct UPCInfo {
    int UPC;
    ManufacturerInfo* mInfo;
    bool alias;
};

class ManufacturerData {
    public:
        ManufacturerData(ifstream& inFile, bool useRBT);
        ~ManufacturerData();
        UPCInfo** allUPCs;
        void sortByUPCorName(bool byUPC) { mergeSort(byUPC, 0, _numUPCs - 1); }
        int getNumUPCs() { return _numUPCs; }
        ManufacturerInfo* findByUPC(int UPC, int start, int end);
        bool addItem(int UPC, long fullCode, string description);
        friend ostream& operator<<(ostream& os, const ManufacturerData&);
        void findAliases();
        void printReport();
        void toHashTable();
        void freeUPCarray();
        bool redBlackTree;

    private:
        void mergeSort(bool byUPC, int start, int end);
        void merge(bool byUPC, int start, int middle, int end);
        void resizeAllUPCs();
        unsigned long _numUPCs;
        unsigned long _sizeAllUPCs;
        StaticHashTable _allMfrCodes;
};
