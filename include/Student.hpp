#pragma once
#include "Global.hpp"
#include "User.hpp"
#include "OfferedCourse.hpp"
#include "Major.hpp"
class Student : public User{
private:
    static const string GET_COURSE_STR; 
    static const string DELETE_COURSE_STR; 

private:
    Major* major;
    int semester;
    vector<OfferedCourse*> courses;
    OfferedCourse* findCourse(int id);
public:
    Student(int id, string name, Major* major, int semester, string password);
    void getPersonalPage(vector<string> &output);
    string getPrint();
    int getSemester();
    void addCourse(OfferedCourse* offered_course);
    void deleteCourse(int id);
    void viewCourses(vector<string> &output);
    string getMajorName();
};