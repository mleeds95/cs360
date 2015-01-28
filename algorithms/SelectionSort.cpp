// File: SelectionSort.cpp
// Worst Case: O(n^2)
// Best Case: O(n^2)

#include <iostream>
#include <stdlib.h>

void printArray(int* arr, int size);
void selectionSort(int* arr, int size);

int main() {
	int arrlength = 15;
	int* arr = new int[arrlength];
    for (int i = 0; i < arrlength; i++) {
        arr[i] = rand() % 100;
    }
	std::cout << "start: ";
	printArray(arr, arrlength);
	std::cout << "\n";
	selectionSort(arr, arrlength);
	std::cout << "end: ";
	printArray(arr, arrlength);
	std::cout << "\n";
	delete []arr;
	return 0;
}

void printArray(int* arr, int size) {
	std::cout << "[";
	for (int i = 0; i < size; i++) {
		std::cout << arr[i];
		if (i != size - 1) std::cout << ",";
	}
	std::cout << "]";
}

void selectionSort(int* arr, int arrlength) {
	int i, j, k, temp;
	for (i = 0; i < arrlength; i++) {
		j = i;
		for (k = i + 1; k < arrlength; k++) {
			if (arr[k] < arr[j]) {
				j = k;
			}
		}
		if (j != i) {
			temp = arr[i];
			arr[i] = arr[j];
			arr[j] = temp;
		}	
	}
}
