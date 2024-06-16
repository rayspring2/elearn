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
    static const string TA_REQUEST_NOTIF_STR;
    static const string ACCEPTED_STR;
    static const string REJECTED_STR;
    static const string NEW_COURSE_POST_STR;


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
    bool isStudent(User* user);
    bool isProfessor(User* user);
    bool isAdmin(User* user);
    bool isTaForm(Post* post);



public:
    System();
    void readData( char* argv[] );
    void addMajor(Major* m);
    void addCourse(Course* c);
    void addUser(User* u);
    void addPost(string title, string message, string image_path);
    bool isLoggedIn();
    void login(int id, string password);
    void logout();
    string printCourseList();
    void printCourse(int id, vector<string> &output); 

    void deletePost(int id);
    void getPersonalPage(int id, vector<string> &output);
    void viewPost(int user_id, int post_id, vector<string> &output);
    void connect(int id);
    void viewNotification(vector<string> &output);
    void courseOffer(int course_id, int professor_id,int capacity, Time time, Date exame_date, int class_numebr);
    void addStudentCourse(int course_id);
    void deleteCourse(int id);
    string viewMyCourses();
    bool userIsStudent();
    bool userIsProfessor();
    bool userIsAdmin();

    void setUserProfilePhoto(string profile_photo_path);
    void addCoursePost(int offered_course_id, string title, string message, string image_path);
    void viewCourseChannel(int course_id, vector<string> &output);
    void ViewCourseChannelPost(int course_id, int post_id, vector<string> &output);
    
    void addTAForm(int course_id, string message);
    void addTaRequest(int professor_id, int form_id);
    vector<string> getApplicantsPrint(int id, vector<string> &output);
    void applyAcceptedTa(vector<bool> applicants_acceptance_status, int form_id);
    
    
    int getUserid(int user_id);
    string getUserName(int user_id);
    string getUserMajor(int user_id);
    string getUserProfilePhotoUrl(int user_id );
    vector<Post*> getUserPosts();
    int getUserNextPostId();
    Post* findUserPost(int id);
};
