#include "User.hpp"

User::User(int id, string name, string password) : id(id), name(name), password(password) {}

void User::print(){
    cout << "id = " << id << endl;
    cout << "name = " << name << endl;
    cout << "password = " << password << endl;
}
bool User::idIsEqualTo(int id_2){
    return id == id_2;
}
bool User::PasswordisEqualTo( string password_2){
    return password == password_2;
}
void User::addNewPost(string title, string message){
    int id =(int)posts.size()+ 1;
    if(!posts.empty())
        id = max(id , posts.back()->getId()+1);
    
    Post* new_post = new Post(id, title, message );
    posts.push_back(new_post);
    sendNotification();
}

void User::sendNotification(){
}

int User::getId(){
    return id;
}
string User::getName(){
    return name;
}
void User::deletePost(int id){
    auto it = find_if(posts.begin(), posts.end(), [id]( Post* &p ){
        return p->getId() == id;
    });
    if(it == posts.end())
        throw runtime_error(NOTFOUND);
    delete *it;
    posts.erase(it);
}