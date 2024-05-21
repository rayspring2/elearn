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