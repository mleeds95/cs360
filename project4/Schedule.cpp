// File: Schedule.cpp
// Author: Matthew Leeds
// Last Edit: 2015-03-11

#include <iostream>
#include <cstdlib>
#include <string>
#include <cmath>
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
    delete[] _optimalSchedule;
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

// radix sort activities by making calls to counting sort for each digit
void Schedule::sortByFinishTime() {
    short numDigits = (uint) ceil(log10((double)_endTime + 1));
    for (short i = 0; i < numDigits; i++) {
        _countingSort(i);
    }
}

void Schedule::_countingSort(short digit) {
    uint* counts = new uint[10](); // initialize to 0
    // First count the number of instances of each possible value
    for (uint i = 0; i < _numActivities; i++) {
        short thisDigit = (_Activities[i]->getFinishTime() / (uint)pow(10, digit)) % 10;
        counts[thisDigit]++;
    }
    // Now calculate the correct indices for each.
    for (uint i = 1; i < 10; i++)
        counts[i] += counts[i-1];
    // Copy elements into their final positions using another array
    Activity** sortedActivities = new Activity*[_numActivities];
    for (int i = _numActivities - 1; i >= 0; i--) {
        short thisDigit = (_Activities[i]->getFinishTime() / (uint)pow(10, digit)) % 10;
        sortedActivities[counts[thisDigit] - 1] = _Activities[i];
        counts[thisDigit]--;
    }
    // point _Activities to the sorted version
    //delete[] _Activities;
    //_Activities = sortedActivities;
    for (uint i = 0; i < _numActivities; i++) {
        _Activities[i] = sortedActivities[i];
    }
    // free memory
    delete[] counts;
    delete[] sortedActivities;
}

// Use a greedy strategy (picking the earliest-finishing compatible activity)
// to find a maximally filled schedule in linear time.
void Schedule::findOptimalSchedule() {
    if (_numActivities == 0)
        return;
    _optimalSchedule = new Activity*[_numActivities];
    _optimalSchedule[0] = _Activities[0];
    uint j = 0; // index of last chosen activity
    for (uint i = 1; i < _numActivities; i++) {
        if (_Activities[i]->getStartTime() >= _Activities[j]->getFinishTime())
            _optimalSchedule[++j] = _Activities[i];
    }
    _numUsedActivities = j + 1;
}

// print the contents of _optimalSchedule to stdout
void Schedule::printOptimalSchedule() {
    cout << "Schedule" << endl;
    for (uint i = 0; i < _numUsedActivities; i++) {
        Activity* pActivity = _optimalSchedule[i];
        cout << pActivity->getName();
        cout << " from " << pActivity->getStartTime() << " to " << pActivity->getFinishTime() << endl;
    }
}
