#include "OfferedCourse.hpp"

OfferedCourse::OfferedCourse(Course* course, Professor* professor, int capacity,Time time, Date exame_date, int class_numebr):
course(course), professor(professor), capacity(capacity), time(time), exame_date(exame_date), class_numebr(class_numebr){
    
    if(!course->majorHas(professor->getMajorId())){
        throw runtime_error(PERMISSIONDENIED);
    }

}

int OfferedCourse::getProfessorId(){
    return professor->getId();
}

bool OfferedCourse::hasTimeConflict(OfferedCourse* course){
    return time.hasConflict(course->time);
}
bool OfferedCourse::hasExamDayConflict(OfferedCourse* course){
    return exame_date.isEqual(course -> exame_date);
}
int OfferedCourse::getCourseId(){
    return course->getId();
}
Course* OfferedCourse::getCourse(){
    return course;
}

void OfferedCourse::print(){
    cout << course->getId() << ' ' << course->getName() << ' ' << capacity <<
    professor->getName() << ' ';
    time.print();
    cout <<' ';
    exame_date.print();
    cout << ' ' << class_numebr << endl;
}
