#pragma once

#include "Global.hpp"

class Notification{
private:
    int id;
    string name;
    string type;
public:
    Notification(int id, string name, string type);
    void print();
};