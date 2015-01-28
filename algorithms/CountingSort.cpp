// File: CountingSort.cpp
// Author: Matthew Leeds
// Last Edit: 2015-01-28
// Running Time: Theta(n)

#include <iostream>
#include <stdlib.h>

using namespace std;

void printArray(int* arr, int size);
void countValues(int* arr, int arrSize, int* auxArr);
void getPositions(int* auxArr, int auxArrSize);
int* countSort(int* arr, int arrSize, int* auxArr);

int main() {
    int arrlength = 15;
    int* arr = new int[arrlength];
    for (int i = 0; i < arrlength; i++) {
        arr[i] = rand() % 100;
    }
    cout << "start: ";
    printArray(arr, arrlength);
    cout << "\n";
    int k = 99; // max value in arr
    int* auxArr = new int[k+1]();
    countValues(arr, arrlength, auxArr);
    getPositions(auxArr, k);
    int* sortedArr = countSort(arr, arrlength, auxArr);
    cout << "end: ";
    printArray(sortedArr, arrlength);
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

void countValues(int* arr, int arrSize, int* auxArr) {
    for (int i = 0; i < arrSize; i++) {
        auxArr[arr[i]]++;
    }
}

void getPositions(int* auxArr, int auxArrSize) {
    for (int i = 1; i < auxArrSize; i++) {
        auxArr[i] += auxArr[i-1];
    }
}

int* countSort(int* arr, int arrSize, int* auxArr) {
    int* sortedArr = new int[arrSize - 1];
    for (int i = arrSize - 1; i >= 0; i--) {
        sortedArr[auxArr[arr[i]] - 1] = arr[i];
        auxArr[arr[i]]--;
    }
    return sortedArr;
}
