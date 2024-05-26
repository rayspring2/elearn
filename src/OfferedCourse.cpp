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
    string outstr = to_string(id) + ' ' + course->getName() + ' ' + to_string(capacity) + ' ' + professor_name + '\n';
    output.push_back(outstr);
}
void OfferedCourse::detailedPrint(vector<string> &output){
    string outstr =  to_string(id) + ' ' + course->getName() + ' ' + to_string(capacity) + ' ' +
    professor_name + ' ' + time.getPrint() + ' ' + exame_date.getPrint() +
    ' ' + to_string(class_numebr) + '\n';
    output.push_back(outstr);

}
