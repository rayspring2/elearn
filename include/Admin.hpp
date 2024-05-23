#pragma once
#include "Global.hpp"
#include "User.hpp"

class Admin : public User{
private:
    static const int ADMIN_DEFAULT_ID;
    static const string ADMIN_DEFAULT_NAME;
    static const string ADMIN_DEFAULT_PASSWORD;
public:
    Admin(int id = ADMIN_DEFAULT_ID, string name = ADMIN_DEFAULT_NAME, string password = ADMIN_DEFAULT_PASSWORD);
    //adding a new course

};