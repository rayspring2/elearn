#pragma once
#include "Global.hpp"

class Date{
private:
    int year,month,day;
    static const char DATE_DELIM;

public:
    Date(string date_str);
    bool isEqual(Date x);
    string getPrint();
};