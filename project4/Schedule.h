// File: Schedule.h
// Author: Matthew Leeds
// Last Edit: 2015-03-11

#pragma once
#include "Activity.h"

typedef unsigned int uint;

using namespace std;

class Schedule {
    public:
        Schedule(); // reads in _endTime and _numActivities
        ~Schedule();
        void recordActivities(); // reads all activities from stdin
        void sortByFinishTime();
        void findOptimalSchedule(); // uses an optimal greedy algorithm
        void printOptimalSchedule();
        
    private:
        uint _endTime; // >= latest finish time
        uint _numActivities; // total number of activities
        uint _numUsedActivities; // nmuber used in optimal schedule
        Activity** _Activities; // all activities
        Activity** _optimalSchedule; // schedule with maximum resource usage
        void _countingSort(short digit);
};
