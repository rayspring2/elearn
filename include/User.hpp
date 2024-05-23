#pragma once
#include "Post.hpp"

class User{
protected:
    int id;
    string name;
    string password;
    vector<Post*> posts;
    vector<Post*> notifications;
    vector<User*>  connections;

public:
    User(int id, string name, string password);
    bool idIsEqualTo(int id_2);
    bool PasswordisEqualTo( string password_2);
    void addNewPost(string title, string message);
    void sendNotification();
    virtual void print();
};