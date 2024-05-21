#pragma once
#include "Post.hpp"

class User{
protected:
    string name;
    string password;

public:
    int id;
    //
    User(int id, string name, string password);
    bool idIsEqualTo(int id_2);
    bool PasswordisEqualTo( string password_2);
    virtual void print();
};