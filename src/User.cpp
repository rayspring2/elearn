#include "User.hpp"
const string User::NEW_POST_STR = "New Post";
User::User(int id, string name, string password) : id(id), name(name), password(password) {}
bool User::idIsEqualTo(int id_2){
    return id == id_2;
}
bool User::PasswordisEqualTo( string password_2){
    return password == password_2;
}
void User::addNewPost(string title, string message, string image_path){
    cnt_posts++;
    int id = cnt_posts;
    Post* new_post = new Post(id, title, message, image_path );
    posts.push_back(new_post);
    sendNotification(NEW_POST_STR);
}

void User::sendNotification( string type){
    Notification* new_notif = new Notification(id, name, type);
    for( User* u : connections){
        u->addNotification(new_notif);
    }
}
void User::sendNotification(Notification* new_notif){
    for( User* u : connections){
        u->addNotification(new_notif);
    }
}
void User::sendNotification(int id, string name, string type){
    Notification* new_notif = new Notification(id, name, type);
    sendNotification(new_notif);
}
void User::addNotification( Notification* notif){
    notifications.push_back(notif);
}

int User::getId(){
    return id;
}

string User::getName(){
    return name;
}

void User::deletePost(int id){
    Post* post = findPost(id);
    delete post;
    posts.erase(find(posts.begin(), posts.end(), post));
}

Post* User::findPost(int id){
    auto it = find_if(posts.begin(), posts.end(), [id]( Post* &p ){
        return p->getId() == id;
    });
    if(it == posts.end())
        throw runtime_error(NOTFOUND);
    return *it;
}

void User::printPost(int id){
    Post* post = findPost(id);
    post->print();
}

void User::connect(User* user){
    auto it = find(connections.begin(), connections.end(), user);
    if( it != connections.end())
        throw runtime_error(BADREQUEST);
    connections.push_back(user);
    user->connections.push_back(this);
}

void User::viewNotifications(vector<string> &output){
    if(notifications.empty())
        throw runtime_error(EMPTYLIST);
    for(int i = notifications.size() - 1 ; i >= 0; i--){
        output.push_back(notifications[i]->getPrint());
    }
    notifications.clear();
}

void User::printAllPosts(vector<string> &output){
    for( int i = posts.size() - 1 ; i >= 0; i-- ){
        output.push_back(posts[i]->getShortPrint());
    }
}

void User::setProfilePhotoUrl(string profile_photo){
    profile_photo_path_url = profile_photo;
}

string User::getProfilePhotoUrl(){
    return profile_photo_path_url;
}
