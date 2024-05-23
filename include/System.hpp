#pragma once
#include "Global.hpp"
#include "User.hpp"
#include "Subject.hpp"
#include "Major.hpp"
#include "Professor.hpp"
#include "Student.hpp"

#define NOT_LOGIN nullptr
#define USER_NOTFPUND nullptr

#define MAJORSPATH argv[1]
#define SUBJECTSPATH argv[2]
#define PROFESSORPATH argv[3]
#define STUDENTPATH argv[4]

class System{
private:
    User* current_user = NOT_LOGIN;
    vector<User*> users;
    vector<Subject*> subjects;
    vector<Major*> majors;
    void readMajorData(ifstream &major_file);
    void readSubjectData(ifstream &subject_file);
    void readProfessorData(ifstream &professor_file);
    void readStudentData(ifstream &student_file);
    Major* findMajor(int id);

public:
	void run();
    void readData( char* argv[] );
    void addMajor(Major* m);
    void addSubject(Subject* c);
    void addUser(User* u);
    void addPost(string title, string message);
    bool isLoggedIn();
    void login(int id, string password);
    void logout();
    void printCourseList();
    void deletePost(int id);
    void getPersonalPage(int id);
};
