// File: Schedule.h
// Author: Matthew Leeds
// Last Edit: 2015-03-09

#pragma once
#include "Activity.h"

typedef unsigned int uint;

using namespace std;

class Schedule {
    public:
        Schedule();
        ~Schedule();
        void recordActivities();
        void sortByFinishTime();
        void findOptimalSchedule();
        void printOptimalSchedule();
        
    private:
        uint _endTime;
        uint _numActivities;
        Activity** _Activities;
        Activity** _optimalSchedule;
        void _mergeSort(uint start, uint end);
        void _merge(uint start, uint middle, uint end);
};
