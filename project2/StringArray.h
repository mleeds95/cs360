// File: StringArray.h
// Author: Matthew Leeds
// Last Edit: 2015-02-04

#include <string>

using namespace std;

class StringArray {
    public:
        StringArray(int n);
        ~StringArray();
        void append(string* s);
        void resizeArray(bool bigger);
        void sortEvensOrOdds(bool evens);
        int getSize() { return _arrSize;}
        friend ostream& operator<<(ostream&, const StringArray&);
        string* operator[](int index);

    private:
        void mergeSort(int start, int end);
        void merge(int start, int middle, int end);
        string** _arr;
        int _arrSize;
        int _arrFilled;
};
