// File: StringData.h
// Author: Matthew Leeds
// Last Edit: 2015-02-02
// Purpose: This is the base class for ManufacturerData and SalesData.
// Its main job is to hold an array of strings.

#include <string>
#include <iostream>

using namespace std;

class StringData {
    public:
        StringData() {}
        ~StringData() {}
        friend ostream& operator<<(ostream&, const StringData&);
        void trimQuotes(string&);
        void sortEvensOrOdds(bool evens);

    protected:
        string** _arr;
        int _arrSize;
        int _numFilled;
        void resizeArray(bool bigger);
        void mergeSort(int start, int end);
        void merge(int start, int middle, int end);
};
