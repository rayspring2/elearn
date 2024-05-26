#pragma once
#include "Global.hpp"

class Major{
private:
    int id;
    string name;

public:
    Major(int id, string name);
    int getId();
    string getName();
};