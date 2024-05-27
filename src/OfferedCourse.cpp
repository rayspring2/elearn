#include "OfferedCourse.hpp"

OfferedCourse::OfferedCourse(int id, Course* course, int professor_id, 
string professor_name, int capacity,Time time, Date exame_date, int class_numebr):
id(id), course(course), professor_id(professor_id), professor_name(professor_name), 
capacity(capacity), time(time), exame_date(exame_date), class_numebr(class_numebr){
}

int OfferedCourse::getProfessorId(){
    return professor_id;
}

bool OfferedCourse::hasTimeConflict(OfferedCourse* course){
    return time.hasConflict(course->time);
}
bool OfferedCourse::hasExamDayConflict(OfferedCourse* course){
    return exame_date.isEqual(course -> exame_date);
}
int OfferedCourse::getId(){
    return id;
}
Course* OfferedCourse::getCourse(){
    return course;
}

void OfferedCourse::shortPrint(vector<string> &output){
    string outstr = to_string(id) + SPACE + course->getName() + SPACE + to_string(capacity) + SPACE + professor_name + NEXTLINE;
    output.push_back(outstr);
}
void OfferedCourse::detailedPrint(vector<string> &output){
    string outstr =  to_string(id) + SPACE + course->getName() + SPACE + to_string(capacity) + SPACE +
    professor_name + SPACE + time.getPrint() + SPACE + exame_date.getPrint() +
    SPACE + to_string(class_numebr) + NEXTLINE;
    output.push_back(outstr);

}
