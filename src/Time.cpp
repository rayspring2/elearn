#include "Time.hpp"

Time::Time(string time_str){
    auto pos = time_str.find(":");
    if(pos == string::npos){
        throw runtime_error(BADREQUEST);
    }

    day = time_str.substr(0, pos);
    transform(day.begin(), day.end(), day.begin(), [](char c){return tolower(c);});
    time_str = time_str.substr(pos+1);
    if(find(WEEKDAYS.begin(), WEEKDAYS.end(), day) == WEEKDAYS.end()){
        throw runtime_error(BADREQUEST);
    }

    pos = time_str.find("-");
    if(pos == string::npos){
        throw runtime_error(BADREQUEST);
    }

    begin_time = stoi( time_str.substr(0 , pos));
    end_time = stoi( time_str.substr( pos+1 ));
}

bool Time::hasConflict(Time time){
    if(day != time.day )
        return 0;
    if(time.end_time <= begin_time || end_time <= time.begin_time  )
        return 0;
    return 1;
}
