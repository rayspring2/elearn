#pragma once
#include "Global.hpp"
#include "User.hpp"
#include "Course.hpp"
#include "Major.hpp"
#include "Professor.hpp"
#include "Student.hpp"

const string GETCMD = "GET";
const string PUTCMD = "PUT";
const string POSTCMD = "POST";
const string DELETECMD = "DELETE";

const char REQUESTDELIMITER = '?';
const string LOGIN_STR = "login";
const string LOGOUT_STR = "logout";
const string ID_FLAG = "id";
const string PASSWORD_FLAG = "password";
const string COURSES_STR = "courses";
#define NOT_LOGIN nullptr
#define USER_NOTFPUND nullptr
class System{
private:
    User* current_user = NOT_LOGIN;
    vector<User*> users;
    vector<Course*> courses;
    vector<Major*> majors;
    void getCmd(stringstream &commandline, string command); //output al list or with id ouput details
    void postCmd(stringstream &commandline, string command);
    void deleteCmd(stringstream &commandline, string command);
    void putCmd(stringstream &commandline, string command);
    
    void readMajorData(ifstream &major_file);
    void readCourseData(ifstream &course_file);
    void readProfessorData(ifstream &professor_file);
    void readStudentData(ifstream &student_file);

    void login(stringstream &commandline);
    void getIdPassword(stringstream &commandline , int &id , string &password);
    void logout(stringstream &commandline);
    istream& inputCommand(stringstream &command);
    bool isLoggedIn();

    void printCourseList();
public:
    //void inputCommand();
    void readData( ifstream &majors_file, ifstream &courses_file, ifstream &professors_file, ifstream &students_file );
    void handleInput();
    void run();
    void addMajor(Major* m);
    void addCourse(Course* c);
    void addUser(User* u);
};
