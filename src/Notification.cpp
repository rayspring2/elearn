#include "Notification.hpp"
const char Notification::NOTIF_DELIM = ':';
Notification::Notification(int id, string name, string type):
id(id) , name(name), type(type) {
    
}
string Notification::getPrint(){
    return  to_string(id) + SPACE + name + NOTIF_DELIM + SPACE + type + NEXTLINE;
}
