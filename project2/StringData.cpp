// File: StringData.cpp
// Author: Matthew Leeds
// Last Edit: 2015-02-02

#include "StringData.h"

using namespace std;

// This resizes _arr to twice as big or down to the space that's actually used,
// depending on the 'bigger' parameter.
void StringData::resizeArray(bool bigger) {
    int newSize;
    if (bigger)
        newSize = _arrSize * 2;
    else
        newSize = _numFilled;
    if (newSize != _arrSize) {
        string** largerArr = new string*[newSize];
        for (int i = 0; i < _numFilled; i++) {
            largerArr[i] = _arr[i];
        }
        delete _arr;
        _arr = largerArr;
        _arrSize = newSize;
    }
}

// Trim " from both sides of a string, and replace instances of "" with ".
void StringData::trimQuotes(string& t) {
    if (t[0] == '"') t = t.substr(1);
    if (t[t.length() - 1] == '"') t = t.substr(0, t.length() - 1);
    size_t found = t.find("\"\"");
    while (found != string::npos) {
        t = t.erase(found, 1);
        found = t.find("\"\"");
    }
}

// Use merge sort on _arr either for even or odd indices.
void mergeSortEvensOrOdds(bool evens) {
    //TODO
}

// Print the array to stdout, one record per line.
ostream& operator<<(ostream& os, const StringData& s) {
    for (int i = 0; i < s._arrSize; i++) {
        os << *s._arr[i] << endl;
    }
    return os;
}
