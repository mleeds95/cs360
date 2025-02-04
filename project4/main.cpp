// File: main.cpp
// Author: Matthew Leeds
// Purpose: CS 360, Project 4 (activity scheduling)
// Last Edit: 2015-03-11

#include "Schedule.h"

using namespace std;

int main() {
    Schedule* pSchedule = new Schedule();
    pSchedule->recordActivities();
    pSchedule->sortByFinishTime();
    pSchedule->findOptimalSchedule();
    pSchedule->printOptimalSchedule();
    delete pSchedule;
    return 0;
}
