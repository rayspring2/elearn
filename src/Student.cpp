#include "Student.hpp"

Student::Student(int id, string name, Major* major, int semester, string password) :
major(major), semester(semester), User(id, name, password){}

void Student::print(){
    cout << name << ' ' << major->getName() << ' ' << semester;
    for(OfferedCourse* s : courses){
        cout << s->getCourse()->getName();
        if(s != courses.back())
            cout << ',';
    }
    cout << endl;
}

void Student::getPersonalPage(){
    print();
    for(Post* p : posts){
        p->shortPrint();
    }
}

void Student::addCourse(OfferedCourse* offered_course){
    Course* course = offered_course->getCourse();
    if(semester < course->getPrequisite())
        throw runtime_error(PERMISSIONDENIED);
    
    for(OfferedCourse* c : courses){
        if(c->hasTimeConflict(offered_course))
            throw runtime_error(PERMISSIONDENIED);
        if(c->hasExamDayConflict(offered_course))
            throw runtime_error(PERMISSIONDENIED);
    }
    courses.push_back(offered_course);
}

void Student::deleteCourse(int id){
    OfferedCourse* course = findCourse(id);
    delete course;
    courses.erase(find(courses.begin(), courses.end(), course ));
}

OfferedCourse* Student::findCourse(int id){
    auto it = find_if(courses.begin(), courses.end(), [id](OfferedCourse* c){
        return c->getCourseId() == id;
    });

    if(it == courses.end())
        throw runtime_error(NOTFOUND);

    return *it;
}

void Student::viewCourses(){
    if(courses.empty())
        throw runtime_error(EMPTYLIST);
    for(auto c : courses){
        c->print();
    }
}

