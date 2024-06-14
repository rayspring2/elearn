#pragma once
#include "Post.hpp"
#include "Notification.hpp"
class User{
private:
    static const string NEW_POST_STR;
protected:
    int cnt_posts = 0;
    int id;
    string name;
    string password;
    string profile_photo_path_url = EMPTYPIC;
    vector<Post*> posts;
    vector<Notification*> notifications;
    vector<User*>  connections;

public:
    User(int id, string name, string password);
    Post* findPost(int id);
    bool idIsEqualTo(int id_2);
    bool PasswordisEqualTo( string password_2);
    void addNewPost(string title, string message, string image_path);
    void sendNotification(string type);
    void sendNotification(Notification* new_notif);
    void sendNotification(int id, string name, string type);
    virtual void getPersonalPage(vector<string> &output){}
    void deletePost(int id);
    int getId();
    string getName();
    virtual string getPrint(){};
    void printPost(int id);
    void connect(User* user);
    void viewNotifications(vector<string> &output);
    void addNotification( Notification* notif);
    void printAllPosts(vector<string> &output);
    
    void setProfilePhotoUrl(string profile_photo);
    string getProfilePhotoUrl();

};