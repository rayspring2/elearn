#pragma once
#include "Global.hpp"

class Time{
private:
    const vector<string> WEEKDAYS {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

public:
    string day;
    int begin_time;
    int end_time;
    Time(string time_str);
    bool hasConflict(Time time);
    void print();
};