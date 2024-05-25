#pragma once
#include "Global.hpp"
#include "User.hpp"
#include "Course.hpp"
#include "OfferedCourse.hpp"
#include "Major.hpp"
#include "Professor.hpp"
#include "Student.hpp"
#include "Admin.hpp"
#include "Time.hpp"
#include "Date.hpp"

#define NOT_LOGIN nullptr
#define USER_NOTFPUND nullptr

#define MAJORSPATH argv[1]
#define COURSESPATH argv[2]
#define PROFESSORPATH argv[3]
#define STUDENTPATH argv[4]

class System{
private:
    static const string NEW_COURSE_OFFERING_STR;
private:
    Admin* admin = new Admin();
    User* current_user = NOT_LOGIN;
    vector<User*> users;
    vector<Course*> courses;
    vector<OfferedCourse*> offered_courses;
    vector<Major*> majors;
    void readMajorData(ifstream &major_file);
    void readCourseData(ifstream &course_file);
    void readProfessorData(ifstream &professor_file);
    void readStudentData(ifstream &student_file);
    Major* findMajor(int id);
    User* findUser(int id);
    Course* findCourse(int id);
    bool prevCourseshasConflictWith(OfferedCourse* new_course);
    OfferedCourse* findOfferedCourse(int course_id);


public:
    System();
	void run();
    void readData( char* argv[] );
    void addMajor(Major* m);
    void addCourse(Course* c);
    void addUser(User* u);
    void addPost(string title, string message);
    bool isLoggedIn();
    void login(int id, string password);
    void logout();
    void printCourseList();
    void printCourse(int id); 

    void deletePost(int id);
    void getPersonalPage(int id);
    void viewPost(int user_id, int post_id);
    void connect(int id);
    void viewNotification();
    void courseOffer(int course_id, int professor_id,int capacity, Time time, Date exame_date, int class_numebr);
    void addStudentCourse(int course_id);
    void deleteCourse(int id);
    void viewMyCourses();
    bool userIsStudent();
    bool userIsProfessor();
    bool userIsAdmin();


};
