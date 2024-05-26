#include "Notification.hpp"

Notification::Notification(int id, string name, string type):
id(id) , name(name), type(type) {
    
}
string Notification::getPrint(){
    return  to_string(id) + ' ' + name + ": " + type + '\n';
}
