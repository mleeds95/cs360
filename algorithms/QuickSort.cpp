// File: QuickSort.cpp
// Author: Matthew Leeds
// Last Edit: 2015-01-19
// Worst Case: O(n^2)
// Best Case: O(n log n)

#include <iostream>
#include <stdlib.h>

using namespace std;

void printArray(int* arr, int size);
void quickSort(int* arr, int left, int right);
int partition(int* arr, int left, int right);

int main() {
    int arrlength = 15;
    int* arr = new int[15];
    for (int i = 0; i < arrlength; i++) {
        arr[i] = rand() % 100;
    }
    cout << "start: ";
    printArray(arr, arrlength);
    cout << "\n";
    quickSort(arr, 0, arrlength - 1);
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

void quickSort(int* arr, int left, int right) {
    if (left < right) {
        int pivotIndex = partition(arr, left, right);
        quickSort(arr, left, pivotIndex - 1);
        quickSort(arr, pivotIndex + 1, right);
    }
}

int partition(int* arr, int left, int right) {
    int pivotIndex = left + ((right - left) / 2);
    int pivotValue = arr[pivotIndex];
    arr[pivotIndex] = arr[right];
    arr[right] = pivotValue;
    int leftEdge = left;
    for (int i = left; i < right; i++) {
        if (arr[i] < pivotValue) {
            int temp = arr[leftEdge];
            arr[leftEdge] = arr[i];
            arr[i] = temp;
            leftEdge++;
        }
    }
    arr[right] = arr[leftEdge];
    arr[leftEdge] = pivotValue;
    return leftEdge;
}
