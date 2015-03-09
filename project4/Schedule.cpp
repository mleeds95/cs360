// File: Schedule.cpp
// Author: Matthew Leeds
// Last Edit: 2015-03-09

#include <iostream>
#include <cstdlib>
#include <string>
#include "Schedule.h"

Schedule::Schedule() {
    // grab a line from stdin, assume it's "<end time>,<number of activities>"
    string firstRecord;
    cin >> firstRecord;
    _endTime = atoi(firstRecord.substr(0, firstRecord.find(",")).c_str());
    _numActivities = atoi(firstRecord.substr(firstRecord.find(",") + 1).c_str());
}

Schedule::~Schedule() {
    for (uint i = 0; i < _numActivities; i++) {
        delete _Activities[i];
    }
    delete[] _Activities;
}

void Schedule::recordActivities() {
    _Activities = new Activity*[_numActivities];
    // receive activity information from stdin, assume it's "<name>,<start time>,<finish time>"
    for (unsigned int i = 0; i < _numActivities; i++) {
        string thisActivity;
        cin >> thisActivity;
        size_t firstComma = thisActivity.find(",");
        size_t secondComma = thisActivity.find(",", firstComma + 1);
        string activityName = thisActivity.substr(0, firstComma);
        uint activityStart = atoi(thisActivity.substr(firstComma + 1, secondComma - firstComma - 1).c_str());
        uint activityFinish = atoi(thisActivity.substr(secondComma + 1).c_str());
        _Activities[i] = new Activity(activityName, activityStart, activityFinish);
    }
}

// make the initial call to mergeSort to sort activities in order of ascending finish time
void Schedule::sortByFinishTime() {
    _mergeSort(0, _numActivities - 1);
}

// sort in Theta(n lg n) time using a recursive merge sort
void Schedule::_mergeSort(uint start, uint end) {
    if (start < end) {
        uint middle = start + ((end - start) / 2);
        _mergeSort(start, middle);
        _mergeSort(middle + 1, end);
        _merge(start, middle, end);
    }
}

// merge two sorted subarrays of _Activities (order by finish time)
void Schedule::_merge(uint start, uint middle, uint end) {
    // copy the data into two temporary arrays
    uint arr1length = middle - start + 1;
    uint arr2length = end - middle;
    Activity* arr1[arr1length];
    Activity* arr2[arr2length];
    for (uint i = start; i <= middle; i++)
        arr1[i - start] = _Activities[i];
    for (uint j = middle + 1; j <= end; j++)
        arr2[j - middle - 1] = _Activities[j];
    // merge the data sets by copying from one or the other on each iteration
    uint k; // _Activites counter
    uint l = 0; // arr1 counter
    uint m = 0; // arr2 counter
    for (k = start; k <= end; k++) {
        if (l >= arr1length) {
            _Activities[k] = arr2[m];
            m++;
        } else if (m >= arr2length) {
            _Activities[k] = arr1[l];
            l++;
        } else if (arr1[l]->getFinishTime() <= arr2[m]->getFinishTime()) {
            _Activities[k] = arr1[l];
            l++;
        } else {
            _Activities[k] = arr2[m];
            m++;
        }
    }
}

void Schedule::findOptimalSchedule() {
    //TODO
}

void Schedule::printOptimalSchedule() {
    //TODO
}
