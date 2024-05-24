#include "Student.hpp"

Student::Student(int id, string name, Major* major, int semester, string password) :
major(major), semester(semester), User(id, name, password){}

void Student::print(){
    cout << name << ' ' << major->getName() << ' ' << semester;
    for(Course* s : courses){
        cout << s->getName();
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