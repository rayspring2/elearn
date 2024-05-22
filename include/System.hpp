#pragma once
#include "Global.hpp"
#include "User.hpp"
#include "Course.hpp"
#include "Major.hpp"
#include "Professor.hpp"
#include "Student.hpp"

#define NOT_LOGIN nullptr
#define USER_NOTFPUND nullptr

#define MAJORSPATH argv[1]
#define COURSESPATH argv[2]
#define PROFESSORPATH argv[3]
#define STUDENTPATH argv[4]

class System{
private:
    User* current_user = NOT_LOGIN;
    vector<User*> users;
    vector<Course*> courses;
    vector<Major*> majors;
    void readMajorData(ifstream &major_file);
    void readCourseData(ifstream &course_file);
    void readProfessorData(ifstream &professor_file);
    void readStudentData(ifstream &student_file);

public:
	void run();
    void readData( char* argv[] );
    void addMajor(Major* m);
    void addCourse(Course* c);
    void addUser(User* u);
    bool isLoggedIn();
    void login(LoginInfo login_info);
    void logout(string &commandline);
    void printCourseList();
};
