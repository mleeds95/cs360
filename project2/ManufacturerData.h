// File: ManufacturerData.h
// Author: Matthew Leeds
// Last Edit: 2015-02-08

#include <string>
#include <fstream>

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
        ManufacturerData(ifstream& inFile);
        ~ManufacturerData();
        UPCInfo** allUPCs;
        void sortByUPCorName(bool byUPC) { mergeSort(byUPC, 0, _numUPCs - 1); }
        int getNumUPCs() { return _numUPCs; }
        ManufacturerInfo* findByUPC(int UPC, int start, int end);
        bool addItem(int UPC, long fullCode, string description);
        friend ostream& operator<<(ostream& os, const ManufacturerData&);
        void findAliases();
        void printReport();

    private:
        void mergeSort(bool byUPC, int start, int end);
        void merge(bool byUPC, int start, int middle, int end);
        void resizeAllUPCs();
        int _numUPCs;
        int _sizeAllUPCs;
};
