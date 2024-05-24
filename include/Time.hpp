#pragma once
#include "Global.hpp"

class Time{
private:
    const vector<string> WEEKDAYS {"sunday", "monday", "tuesday", "wednesday", "thursday", "friday", "saturday"};

public:
    string day;
    int begin_time;
    int end_time;
    Time(string time_str);
    bool hasConflict(Time time);
};