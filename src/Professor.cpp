#include "Professor.hpp"


Professor::Professor(int id, string name, Major* major, string pos, string password) :
    major(major) , User(id, name, password) {
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
int Professor::getMajorId(){
    return major->getId();
}
string Professor::getPrint(){
    string outstr =  name + ' ' + major->getName() + ' ' + getPositionAsString() + ' ';
    for(OfferedCourse* s : courses){
        outstr = outstr + s -> getCourse() -> getName();
        if(s != courses.back())
            outstr = outstr + ',';
    }
    outstr = outstr + '\n';
    return outstr;
}
void Professor::getPersonalPage(vector<string> &output){
    output.push_back(getPrint());
    printAllPosts(output);
}
void Professor::addCourse(OfferedCourse* course){
    courses.push_back(course);
}
