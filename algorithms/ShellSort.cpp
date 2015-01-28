// File: Shellsort.cpp
// Author: Matthew Leeds
// Last Edit: 2015-01-16
// Worst Case: O(n^2)
// Best Case: O(n lg^2 n)

#include <iostream>
#include <stdlib.h>

using namespace std;

void printArray(int* arr, int size);
void hSort(int* arr, int size, int h);

int main() {
    int arrlength = 15;
    int* arr = new int[arrlength];
    for (int i = 0; i < arrlength; i++) {
        arr[i] = rand() % 100;
    }
    cout << "start: ";
    printArray(arr, arrlength);
    cout << "\n";
    for (int k = arrlength / 2; k >= 1; k /= 2) {
        hSort(arr, arrlength, k);
    }
    //hSort(arr, arrlength, 1);
    cout << "end: ";
    printArray(arr, arrlength);
    cout << "\n";
    delete []arr;
    return 0;
}

void printArray(int* arr, int size) {
	cout << "[";
	for (int i = 0; i < size; i++) {
		cout << arr[i];
		if (i != size - 1) cout << ",";
	}
	cout << "]";
}

void hSort(int* arr, int size, int h) {
    int maxVal = (size - (size % h));
    int temp;
    for (int l = h; l < maxVal; l++) {
        for (int m = l; m < size; m += h) {
            int currentLeast = m-h;
            for (int p = m; p < size; p += h) {
                if (arr[p] < arr[currentLeast]) {
                    currentLeast = p;
                }
            }
            if (currentLeast != m-h) {
                temp = arr[m-h];
                arr[m-h] = arr[currentLeast];
                arr[currentLeast] = temp;
            }
        }
    }
}
