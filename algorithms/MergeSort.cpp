// File: MergeSort.cpp
// Worst case: O(n log n)
// Best case: O(n log n)

#include <iostream>

void printArray(int* arr, int size);
void mergeSort(int* arr, int start, int end);
void merge(int* arr, int start, int middle, int end);

int main() {
	int arrlength = 4;
	int* testarr = new int[arrlength];
	testarr[0] = 4; testarr[1] = 1; testarr[2] = 2; testarr[3] = 0;
	std::cout << "start: ";
	printArray(testarr, arrlength);
	std::cout << "\n";
	// make the inital call to mergeSort for the whole array
	mergeSort(testarr, 0, arrlength - 1);
	std::cout << "end: ";
	printArray(testarr, arrlength);
	std::cout << "\n";
	delete []testarr;
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

// This makes recursive calls to itself to split and merge arrays of length > 1
void mergeSort(int* arr, int start, int end) {
	if (start < end) {
		int middle = (start + end) / 2;	
		mergeSort(arr, start, middle);
		mergeSort(arr, middle + 1, end);
		merge(arr, start, middle, end);
	} // else it's already sorted (length 1 or 0)
}

// This merges two sorted subarrays back into the same variable they were in
void merge(int* arr, int start, int middle, int end) {
	// Copy the subarrays so we can overwrite the original.
	int arr1Length = middle - start + 1;
	int arr2Length = end - middle;
	int arr1[arr1Length];
	int arr2[arr2Length];
	int i;
	for (i = start; i <= middle; i++) {
		arr1[i - start]	= arr[i];
	}
	int j;
	for (j = middle + 1; j <= end; j++) {
		arr2[j - middle - 1] = arr[j];
	}
	int l = 0; // arr1 counter
	int m = 0; // arr2 counter
	// Now merge them by copying an element from one or the other each iteration.
	int k; // arr counter
	for (k = start; k <= end; k++) {
		if (l >= arr1Length) {
			arr[k] = arr2[m];
			m++;
		} else if (m >= arr2Length) {
			arr[k] = arr1[l];
			l++;
		} else if (arr1[l] <= arr2[m]) {
			arr[k] = arr1[l];
			l++;
		} else {
			arr[k] = arr2[m];
			m++;
		}
	}
}
