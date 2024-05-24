#include "Date.hpp"

Date::Date(string date_str){
    year = stoi(divString(date_str, '/'));
    month = stoi(divString(date_str, '/'));
    day = stoi(divString(date_str));
}

