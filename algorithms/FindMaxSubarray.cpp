// File: FindMaxSubarray.cpp
// Author: Matthew Leeds
// Last Edit: 2015-01-15
// Purpose: Given an n-length array, this algorithm should be able to find the subarray
// with the largest sum.
// Complexity: Theta(n log n)

#include <iostream>
#include <vector>
#include <limits>

using namespace std;

void printColoredVector(vector<int>*, int start = -1, int end = -1);
vector<int> findMaxCrossingSubarray(vector<int>*, int start, int middle, int end);
vector<int> findMaxSubarray(vector<int>*, int start, int end);

int main() {
    vector<int>* testarr = new vector<int> {13,-3,-25,20,-3,-16,-23,18,20,-7,12,-5,-22,15,-4,7};
    int arrlength = (int) testarr->size();
    cout << "\033[01;34mstart: ";
    printColoredVector(testarr);
    cout << "\n";
    // ideally, we'd check if every value is positive so we don't bother carrying on
    vector<int> result = findMaxSubarray(testarr, 0, arrlength);
    cout << "\033[01;34m  end: ";
    printColoredVector(testarr, result[0], result[1]);
    cout << "\n";
    delete testarr;
    return 0;
}

void printColoredVector(vector<int>* inVector, int start, int end) {
    cout << "\033[01;37m[";
    for (int i = 0; i < (int) inVector->size(); i++) {
        if (i == start) cout << "\033[22;31m";
        cout << (*inVector)[i];
        if (i == end) cout << "\033[01;37m";
        if (i != ((int) inVector->size() - 1)) cout << ",";
    }
    cout << "]";
}

vector<int> findMaxCrossingSubarray(vector<int>* inVector, int start, int middle, int end) {
    // ideally you would error-check start, middle, end
    int leftSum = numeric_limits<int>::min(); // or inVector[middle]
    int sum = 0;
    int maxLeft = middle;
    for (int i = middle; i >= start; i--) {
        sum += (*inVector)[i];
        if (sum > leftSum) {
            leftSum = sum;
            maxLeft = i;
        }
    }
    int rightSum = numeric_limits<int>::min(); // or inVector[middle + 1]
    sum = 0;
    int maxRight = middle + 1;
    for (int j = middle + 1; j <= end; j++) {
        sum += (*inVector)[j];
        if (sum > rightSum) {
            rightSum = sum;
            maxRight = j;
        }
    }
    vector<int> returnVector(3); // left index, right index, sum
    returnVector[0] = maxLeft;
    returnVector[1] = maxRight;
    returnVector[2] = leftSum + rightSum;
    return returnVector;
}

vector<int> findMaxSubarray(vector<int>* inVector, int start, int end) {
    if (start == end) {
       vector<int> returnVector = vector<int>(3); // left index, right index, sum
       returnVector[0] = start;
       returnVector[1] = end;
       returnVector[2] = (*inVector)[start];
       return returnVector; 
    } else {
        int middle = start + ((end - start) / 2);
        vector<int> leftMax = findMaxSubarray(inVector, start, middle);
        vector<int> rightMax = findMaxSubarray(inVector, middle + 1, end);
        vector<int> crossMax = findMaxCrossingSubarray(inVector, start, middle, end);
        if (leftMax[2] >= rightMax[2] && leftMax[2] >= crossMax[2]) return leftMax;
        else if (rightMax[2] >= leftMax[2] && rightMax[2] >= crossMax[2]) return rightMax;
        else return crossMax;
    }
}
