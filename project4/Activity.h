// File: Activity.h
// Author: Matthew Leeds
// Last Edit: 2015-03-09

#pragma once
#include <string>

typedef unsigned int uint;

using namespace std;

class Activity {
    public:
        Activity(string name, uint startTime, uint finishTime) :
            _name(name), _startTime(startTime), _finishTime(finishTime) {};
        ~Activity() {};
        string getName() { return _name; }
        uint getStartTime() { return _startTime; }
        uint getFinishTime() { return _finishTime; }

    private:
        string _name;
        uint _startTime;
        uint _finishTime;
};
