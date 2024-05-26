#pragma once
#include "Global.hpp"
#include "User.hpp"
#include "OfferedCourse.hpp"
#include "Major.hpp"
class Student : public User{
private:
    Major* major;
    int semester;
    vector<OfferedCourse*> courses;
    OfferedCourse* findCourse(int id);
public:
    Student(int id, string name, Major* major, int semester, string password);
    void getPersonalPage(vector<string> &output);
    string getPrint();
    void addCourse(OfferedCourse* offered_course);
    void deleteCourse(int id);
    void viewCourses(vector<string> &output);
};