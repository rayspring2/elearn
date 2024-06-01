#pragma once
#include "Global.hpp"
#include "System.hpp"

class IO{
private:
    static const string GET;
    static const string PUT;
    static const string POST;
    static const string DELETE; 
    static const string REQUESTDELIMITER;

    static const string LOGIN_STR;
    static const string LOGOUT_STR;
    static const string POST_STR;
    static const string COURSES_STR;
    static const string COURSE_OFFER_STR;
    static const string PERSONALPAGE_STR;
    static const string CONNECT_STR;
    static const string NOTIFICATION_STR;
    static const string MYCOURSES_STR;
    static const string PROFILE_PHOTO_STR;
    static const string COURSE_POST_STR;
    static const string COURSE_CHANNEL_STR;
    static const string TA_FORM_STR;
    static const string ID_FLAG;
    static const string PHOTO_FLAG;
    static const string POSTID_FLAG;
    static const string PASSWORD_FLAG;
    static const string TITLE_FLAG;
    static const string MESSAGE_FLAG;
    static const string IMAGE_FLAG;

    static const string COURSE_ID_FLAG;
    static const string PROFESSOR_ID_FLAG;
    static const string CAPACITY_FLAG;
    static const string TIME_FLAG;
    static const string EXAM_DATE_FLAG;
    static const string CLASS_NUMBER_FLAG;

private:
    System utms;
    const vector<string> getcommands = {COURSES_STR, PERSONALPAGE_STR, POST_STR,
     NOTIFICATION_STR, MYCOURSES_STR, COURSE_CHANNEL_STR };
    const vector<string> postcommands = {LOGIN_STR, LOGOUT_STR, POST_STR,
     CONNECT_STR, COURSE_OFFER_STR, PROFILE_PHOTO_STR, COURSE_POST_STR, TA_FORM_STR };
    const vector<string> deletecommands = {POST_STR, MYCOURSES_STR};
    const vector<string> putcommands = {MYCOURSES_STR};
    vector<string> output;   
    void getCmd(string &commandline, string command);
    void postCmd(string &commandline, string command);
    void deleteCmd(string &commandline, string command);
    void putCmd(string &commandline, string command); 
    void printOutput();

    void getCourse(string &commandline);
    void getPersonalPage(string &commandline);
    void getPost(string &commandline);
    void getNotification(string &commandline);
    void getMyCourses(string &commandline);
    void getCourseChannel(string &commandline);

    
    void postLogin(string &commandline);
    void postLogout(string &commandline);
    void postPost(string &commandline);
    void postConnect(string &commandline);
    void postCourseOffer(string &commandline);
    void postProfilePhoto(string &commandline);
    void postCoursePost(string &commandline);
    void postTAForm(string &commandline);


    void deletePost(string &commandline);
    void deleteMycourse(string &commandline);
    void putMyCourse(string &commandline);


public:
    IO(char* argv[]);
    void run();
};
