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

// This recurses to sort the array. helper for mergeSortEvensOrOdds.
void StringData::mergeSort(int start, int end) {
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
void StringData::merge(int start, int middle, int end) {
	// Copy the subarrays so we can overwrite the original.
	int arr1Length = middle - start + 2;
	int arr2Length = end - middle;
	string* arr1[arr1Length];
	string* arr2[arr2Length];
    // Depending on the parity, we should either be copying each element's successor or predecessor.
    int parity = (start % 2 == 0 ? 1 : -1);
	int i;
	for (i = start; i <= middle; i += 2) {
		arr1[i - start]	= _arr[i];
        arr1[i - start + 1] = _arr[i + parity];
	}
	int j;
	for (j = middle + 2; j <= end; j += 2) {
		arr2[j - middle - 2] = _arr[j];
        arr2[j - middle - 1] = _arr[j + parity];
	}
	int l = 0; // arr1 counter
	int m = 0; // arr2 counter
	// Now merge them by copying a pair of elements from one or the other on each iteration.
	int k; // _arr counter
	for (k = start; k <= end; k += 2) {
		if (l >= arr1Length) {
			_arr[k] = arr2[m++];
			_arr[k + parity] = arr2[m++];
		} else if (m >= arr2Length) {
			_arr[k] = arr1[l++];
            _arr[k + parity] = arr1[l++];
		} else if (*arr1[l] <= *arr2[m]) {
			_arr[k] = arr1[l++];
            _arr[k + parity] = arr1[l++];
		} else {
			_arr[k] = arr2[m++];
            _arr[k + parity] = arr2[m++];
		}
	}
}

// Use merge sort on _arr either for even or odd indices.
void StringData::sortEvensOrOdds(bool evens) {
    if (evens)
        mergeSort(0, _arrSize - 2);
    else
        mergeSort(1, _arrSize - 1);
}

// Print the array to stdout, one record per line.
ostream& operator<<(ostream& os, const StringData& s) {
    for (int i = 0; i < s._arrSize; i++) {
        os << *s._arr[i] << endl;
    }
    return os;
}
