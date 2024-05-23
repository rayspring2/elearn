#include "Student.hpp"

Student::Student(int id, string name, Major* major, int semester, string password) :
major(major), semester(semester), User(id, name, password){}

void Student::print(){
    cout << name << ' ' << major->getName() << ' ' << semester;
    for(Subject* s : subjects){
        cout << s->getName();
        if(s != subjects.back())
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