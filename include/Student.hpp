#pragma once
#include "Global.hpp"
#include "User.hpp"
#include "Course.hpp"
class Student : public User{
private:
    int major_id;
    int semester;
    vector<Course*> courses;
public:
    Student(int id, string name, int major_id, int semester, string password);
    void print();
};