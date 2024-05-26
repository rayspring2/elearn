#include "Date.hpp"

Date::Date(string date_str){
    year = getNatrualNumb(divString(date_str, '/'));
    month = getNatrualNumb(divString(date_str, '/'));
    day = getNatrualNumb(divString(date_str));
}
bool Date::isEqual(Date x){
    return (day == x.day) && (month == x.month) && (year == x.year);
}
string Date::getPrint(){
    return  to_string(year) + '/' + to_string(month) + '/' + to_string(day);
}


