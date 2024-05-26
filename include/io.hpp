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

    static const string ID_FLAG;
    static const string POSTID_FLAG;
    static const string PASSWORD_FLAG;
    static const string TITLE_FLAG;
    static const string MESSAGE_FLAG;
    static const string COURSE_ID_FLAG;
    static const string PROFESSOR_ID_FLAG;
    static const string CAPACITY_FLAG;
    static const string TIME_FLAG;
    static const string EXAM_DATE_FLAG;
    static const string CLASS_NUMBER_FLAG;

private:
    System utms;
    const std::string outputfile_name = "outt.txt";
    ofstream file_out;
    const vector<string> getcommands = {COURSES_STR, PERSONALPAGE_STR, POST_STR, NOTIFICATION_STR, MYCOURSES_STR };
    const vector<string> postcommands = {LOGIN_STR, LOGOUT_STR, POST_STR, CONNECT_STR, COURSE_OFFER_STR };
    const vector<string> deletecommands = {POST_STR, MYCOURSES_STR};
    const vector<string> putcommands = {MYCOURSES_STR};
    vector<string> output;   
    void getCmd(string &commandline, string command); //output al list or with id ouput details
    void postCmd(string &commandline, string command);
    void deleteCmd(string &commandline, string command);
    void putCmd(string &commandline, string command); 
    void printOutput();
public:
    IO(char* argv[]);
    void run();
};
