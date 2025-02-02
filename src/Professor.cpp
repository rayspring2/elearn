#include "Professor.hpp"

const string Professor::NEW_FORM_STR = "New Form";


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
    string outstr =  name + SPACE + major->getName() + SPACE + getPositionAsString() + SPACE;
    for(OfferedCourse* s : courses){
        outstr = outstr + s -> getCourse() -> getName();
        if(s != courses.back())
            outstr = outstr + COMMA;
    }
    outstr = outstr + NEXTLINE;
    return outstr;
}
void Professor::getPersonalPage(vector<string> &output){
    output.push_back(getPrint());
    printAllPosts(output);
}
void Professor::addCourse(OfferedCourse* course){
    courses.push_back(course);
}
void Professor::addTAForm(OfferedCourse* offered_course, string message){
    cnt_posts++;
    Course* course = offered_course->getCourse();
    string professor_info = getPrint();
    string course_info = offered_course->getDetailedPrint();
    TAFormPost* new_ta_form = new TAFormPost(course_info, course->getName(), offered_course->getId(), cnt_posts, message, course->getPrequisite());
    posts.push_back(new_ta_form);
    sendNotification(NEW_FORM_STR);
}

TAFormPost* Professor::findTaForm(int id){
    auto it = find_if(posts.begin(), posts.end(), [id]( Post* &p ){
        return p->getId() == id;
    });
    if(it == posts.end())
        throw runtime_error(NOTFOUND);
    if(dynamic_cast<TAFormPost*>(*it))
        return dynamic_cast<TAFormPost*>(*it);
    else 
        throw runtime_error(NOTFOUND);
}

string Professor::getMajorName(){
    return major->getName();
}

