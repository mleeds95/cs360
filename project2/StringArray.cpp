// File: StringArray.cpp
// Author: Matthew Leeds
// Last Edit: 2015-02-04

#include "StringArray.h"
#include <iostream>

using namespace std;

string strToUpper(string);
bool caseInsensitiveStrcmp(const string&, const string&);

StringArray::StringArray(int n) {
    _arrSize = n;
    _arr = new string*[_arrSize];
    _arrFilled = 0;
}

StringArray::~StringArray() {
    for (int i = 0; i < _arrSize; i++) {
        delete _arr[i];
    }
}

void StringArray::append(string* s) {
    if (_arrFilled == _arrSize)
        resizeArray(true);
    _arr[_arrFilled++] = s;
}

// This resizes _arr to twice as big or down to the space that's actually used,
// depending on the 'bigger' parameter. Of course ideally this would be part of
// a separate data structure, but since we're using arrays this makes sense.
void StringArray::resizeArray(bool bigger) {
    int newSize;
    if (bigger)
        newSize = _arrSize * 2;
    else
        newSize = _arrFilled;
    if (newSize != _arrSize) {
        string** largerArr = new string*[newSize];
        for (int i = 0; i < _arrFilled; i++) {
            largerArr[i] = _arr[i];
        }
        delete[] _arr;
        _arr = largerArr;
        _arrSize = newSize;
    }
}

// This recurses to sort the array. helper for mergeSortEvensOrOdds.
void StringArray::mergeSort(int start, int end) {
    if (start < end) {
        int middle = (start + end) / 2;
        // The parity of middle should match that of start.
        if ((middle % 2 == 1 && start % 2 == 0) || (middle % 2 == 0 && start % 2 == 1))
            middle--;
        mergeSort(start, middle);
        mergeSort(middle + 2, end);
        merge(start, middle, end);
    }
}

// This merges two sorted subarrays. helper for mergeSortEvensOrOdds.
void StringArray::merge(int start, int middle, int end) {
    cout << "merge " << start << " middle " << middle << " end " << end << endl;
    // Copy the subarrays into new ones so we can overwrite the original.
    int arr1Length = middle - start + 2;
    int arr2Length = end - middle;
    string** arr1 = new string*[arr1Length];
    string** arr2 = new string*[arr2Length];
    // Depending on the parity, we should either be copying each element's successor or predecessor.
    int parity = (start % 2 == 0 ? 1 : -1);
    // We should also copy elements from odd indices into odd indices, and similarly for even.
    int startParity = (start % 2 == 0 ? 0 : 1);
    for (int i = start; i <= middle; i += 2) {
        arr1[i - start + startParity] = _arr[i];
        arr1[i - start + startParity + parity] = _arr[i + parity];
    }
    for (int j = middle + 2; j <= end; j += 2) {
        arr2[j - middle - 2 + startParity] = _arr[j];
        arr2[j - middle - 2 + startParity + parity] = _arr[j + parity];
    }
    // Now merge them by copying a pair of elements from one or the other on each iteration.
    int l = startParity; // arr1 counter
    int m = startParity; // arr2 counter
    int k; // _arr counter
    for (k = start; k <= end; k += 2) {
        if (l >= arr1Length) {
            _arr[k] = arr2[m];
            _arr[k + parity] = arr2[m + parity];
            m += 2;
        } else if (m >= arr2Length) {
            _arr[k] = arr1[l];
            _arr[k + parity] = arr1[l + parity];
            l += 2;
        } else if (strToUpper(*arr1[l]) <= strToUpper(*arr2[m])) {
            _arr[k] = arr1[l];
            _arr[k + parity] = arr1[l + parity];
            l += 2;
        } else {
            _arr[k] = arr2[m];
            _arr[k + parity] = arr2[m + parity];
            m += 2;
        }
    }
    delete[] arr1;
    delete[] arr2;
}

// Use merge sort on _arr either for even or odd indices.
void StringArray::sortEvensOrOdds(bool evens) {
    if (evens)
        mergeSort(0, _arrSize - 2);
    else
        mergeSort(1, _arrSize - 1);
}

// Assume the array is sorted, the indices given have the same 
// parity and are within range, and the array size has been kept 
// down to what's necessary. Do a binary search for something.
// On success return its successor or predecessor, else the empty string.
string StringArray::searchEvensOrOdds(string str, int start, int end) {
    string strLeft = "";
    string strRight = "";
    int parity = (start % 2 == 0 ? 1 : -1);
    int middle = (start + end) / 2; 
    // The parity of middle should match that of start.
    if ((middle % 2 == 1 && start % 2 == 0) || (middle % 2 == 0 && start % 2 == 1))
        middle--;
    if (caseInsensitiveStrcmp(*_arr[middle], str))
        return *_arr[middle + parity];
    if (start < end) {
        if (*_arr[middle] < str)
            strRight = searchEvensOrOdds(str, middle + 2, end);
        else
            strLeft = searchEvensOrOdds(str, start, middle - 2);
    }
    if (strRight.length() > 0) return strRight;
    if (strLeft.length() > 0) return strLeft;
    return "";
}

// Print the array to stdout, one record per line.
ostream& operator<<(ostream& os, const StringArray& s) {
    for (int i = 0; i < s._arrSize; i++) {
        os << *s._arr[i] << endl;
    }
    return os;
}

string* StringArray::operator[](int index) {
    return _arr[index];
}
