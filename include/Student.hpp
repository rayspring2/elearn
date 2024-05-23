#pragma once
#include "Global.hpp"
#include "User.hpp"
#include "Subject.hpp"
#include "Major.hpp"
class Student : public User{
private:
    Major* major;
    int semester;
    vector<Subject*> subjects;
public:
    Student(int id, string name, Major* major, int semester, string password);
    void getPersonalPage();
    void print();
};