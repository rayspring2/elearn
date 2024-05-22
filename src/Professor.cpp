#include "Professor.hpp"

Professor::Professor(int id, string name, int major_id, string pos, string password) :
    major_id(major_id) , User(id, name, password) {
    setPositionByString(pos);
}
void Professor::setPositionByString(string pos){
    if(pos == INSTRUCTOR_STR)
        position = INSTRUCTOR;
    else if(pos == ASSISTANTPROF_STR)
        position = ASSISTANTPROF;
    else if(pos == ASSOCIATEPROF_STR)
        position = ASSOCIATEPROF;
    else if(pos == PROF_STR){
        position = PROF;
    }
        
    //else should be written
}
string Professor::getPositionAsString(){
    string pos;
    if(position == INSTRUCTOR)
        pos = INSTRUCTOR_STR;
    else if(position == ASSISTANTPROF)
        pos = ASSISTANTPROF_STR;
    else if(position == ASSOCIATEPROF)
        pos = ASSOCIATEPROF_STR;
    else if(position == PROF)
        pos = PROF_STR;
    return pos;
}

void Professor::print(){
    User::print();
    cout << "major_id = " << major_id << endl;
    cout << "position = " << getPositionAsString() << endl;
}