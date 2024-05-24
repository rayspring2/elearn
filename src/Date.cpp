#include "Date.hpp"

Date::Date(string date_str){
    year = stoi(divString(date_str, '/'));
    month = stoi(divString(date_str, '/'));
    day = stoi(divString(date_str));
}
bool Date::isEqual(Date x){
    return (day == x.day) && (month == x.month) && (year == x.year);
}
void Date::print(){
    cout << year <<'/' << month << '/' << day;
}


