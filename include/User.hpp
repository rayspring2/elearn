#pragma once
#include "Post.hpp"
#include "Notification.hpp"
class User{
private:
    static const string NEW_POST_STR;
private:
    Post* findPost(int id);
protected:
    int id;
    string name;
    string password;
    vector<Post*> posts;
    vector<Notification*> notifications;
    vector<User*>  connections;

public:
    User(int id, string name, string password);
    bool idIsEqualTo(int id_2);
    bool PasswordisEqualTo( string password_2);
    void addNewPost(string title, string message);
    void sendNotification(string type);
    virtual void getPersonalPage(){};
    void deletePost(int id);
    int getId();
    string getName();
    virtual void print();
    void printPost(int id);
    void connect(User* user);
    void viewNotifications();
    void addNotification( Notification* notif);

};