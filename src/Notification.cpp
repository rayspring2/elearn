#include "Notification.hpp"

Notification::Notification(int id, string name, string type):
id(id) , name(name), type(type) {
    
}
void Notification::print(){
    cout << id << ' ' << name << ": " << type << endl;
}
