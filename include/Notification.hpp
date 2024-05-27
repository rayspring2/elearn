#pragma once

#include "Global.hpp"

class Notification{
private:
    int id;
    string name;
    string type;
    static const char NOTIF_DELIM;

public:
    Notification(int id, string name, string type);
    string getPrint();
};