#include "Student.hpp"

Student::Student(int id, string name, Major* major, int semester, string password) :
major(major), semester(semester), User(id, name, password){}

string Student::getPrint(){
    string outstr =  name + ' ' + major->getName() + ' ' + to_string(semester) + ' ';
    for(OfferedCourse* s : courses){
        outstr = outstr + s -> getCourse() -> getName();
        if(s != courses.back())
            outstr = outstr + ',';
    }
    outstr = outstr + '\n';
    return outstr;
}

void Student::getPersonalPage(vector<string> &output){
    output.push_back(getPrint());
    printAllPosts(output);
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
    courses.erase(find(courses.begin(), courses.end(), course ));
}

OfferedCourse* Student::findCourse(int id){
    auto it = find_if(courses.begin(), courses.end(), [id](OfferedCourse* c){
        return c->getId() == id;
    });

    if(it == courses.end())
        throw runtime_error(NOTFOUND);

    return *it;
}

void Student::viewCourses(vector<string> &output){
    if(courses.empty())
        throw runtime_error(EMPTYLIST);
    for(auto c : courses){
        c->detailedPrint(output);
    }
}

