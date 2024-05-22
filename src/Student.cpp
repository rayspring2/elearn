#include "Student.hpp"

Student::Student(int id, string name, int major_id, int semester, string password) :
major_id(major_id), semester(semester), User(id, name, password){}

void Student::print(){
    User::print();
    cout << "major_id = " << major_id << endl;
    cout << "semester = " << semester << endl;
}