#include "Student.hpp"

Student::Student(int id, string name, Major* major, int semester, string password) :
major(major), semester(semester), User(id, name, password){}

void Student::print(){
    User::print();
    cout << "major_id = " << major->getId() << endl;
    cout << "semester = " << semester << endl;
}
void Student::getPersonalPage(){
    cout << name << ' ' << major->getName() << ' ' << semester;
    for(Subject* s : subjects){
        cout << s->getName();
        if(s != subjects.back())
            cout << ',';
    }
    cout << endl;
    for(Post* p : posts){
        p->shortPrint();
    }
}