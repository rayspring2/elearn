#pragma once
#include "Global.hpp"

class Date{
private:
    int year,month,day;

public:
    Date(string date_str);
    bool isEqual(Date x);
    void print();
};