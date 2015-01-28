// File: InsertionSort.cpp
// Best case: O(n)
// Worst case: O(n^2)

#include <iostream>

int main() {
	int testarr[] = {3, 2, 1};
	std::cout << "start: [" << testarr[0] << "," << testarr[1] << "," << testarr[2] << "]\n";
	int arrlength = (sizeof(testarr) / sizeof(testarr[0]));
	for (int i = 1; i < arrlength; i++) {
		for (int j = i; j > 0; j--) {
			if (testarr[j] < testarr[j-1]) {
				int temp = testarr[j-1];
				testarr[j-1] = testarr[j];
				testarr[j] = temp;
			} else {
				break;
			}
		}
	}
	std::cout << "end: [" << testarr[0] << "," << testarr[1] << "," << testarr[2] << "]\n";
	return 0;
}	
