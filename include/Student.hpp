#pragma once
#include "Global.hpp"
#include "User.hpp"
#include "Course.hpp"
#include "Major.hpp"
class Student : public User{
private:
    Major* major;
    int semester;
    vector<Course*> courses;
public:
    Student(int id, string name, Major* major, int semester, string password);
    void getPersonalPage();
    void print();
};