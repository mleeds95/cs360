// File: main.cpp
// Author: Matthew Leeds
// Purpose: CS 360, Project 4 (activity scheduling)
// Last Edit: 2015-03-09

#include <iostream>
#include <cstdlib>
#include <string>
#include "Schedule.h"

using namespace std;

int main() {
    Schedule* pSchedule = new Schedule();
    pSchedule->recordActivities();
    pSchedule->sortByFinishTime();
    //pSchedule->findOptimalSchedule();
    //pSchedule->printOptimalSchedule();
    delete pSchedule;
    return 0;
}
