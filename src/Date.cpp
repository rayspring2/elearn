#include "Date.hpp"
const char Date::DATE_DELIM = '/';

Date::Date(string date_str){
    year = getNatrualNumb(divString(date_str, DATE_DELIM));
    month = getNatrualNumb(divString(date_str, DATE_DELIM));
    day = getNatrualNumb(divString(date_str));
}
bool Date::isEqual(Date x){
    return (day == x.day) && (month == x.month) && (year == x.year);
}
string Date::getPrint(){
    return  to_string(year) + DATE_DELIM + to_string(month) + DATE_DELIM + to_string(day);
}


