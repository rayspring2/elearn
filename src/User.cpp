#include "User.hpp"
const string User::NEW_POST_STR = "New Post";
User::User(int id, string name, string password) : id(id), name(name), password(password) {}
bool User::idIsEqualTo(int id_2){
    return id == id_2;
}
bool User::PasswordisEqualTo( string password_2){
    return password == password_2;
}
void User::addNewPost(string title, string message){
    int id =(int)posts.size() + 1;
    if(!posts.empty())
        id = max(id , posts.back()->getId() + 1);
    
    Post* new_post = new Post(id, title, message );
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
    for(Post* p : posts){
        output.push_back(p->getShortPrint());
    }
}
