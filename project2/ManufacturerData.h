// File: ManufacturerData.h
// Author: Matthew Leeds
// Last Edit: 2015-02-01

#include <fstream>
#include <string>

using namespace std;

class ManufacturerData {
    public:
        ManufacturerData(ifstream& inFile);
        ~ManufacturerData();
        void resizeArray(bool bigger);
        friend ostream& operator<<(ostream& os, const ManufacturerData& m);
        void sortByCode();
        void sortByName();

    private:
        string** _arr;
        int _arrSize;
        int _numFilled;
};
