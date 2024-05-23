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
    static const string ID_FLAG;
    static const string POSTID_FLAG;
    static const string PASSWORD_FLAG;
    static const string TITLE_FLAG;
    static const string MESSAGE_FLAG;
    static const string COURSES_STR;
    static const string PERSONALPAGE_STR;
    static const string CONNECT_STR;
    static const string NOTIFICATION_STR;


private:
    System utms;
    void getCmd(string &commandline, string command); //output al list or with id ouput details
    void postCmd(string &commandline, string command);
    void deleteCmd(string &commandline, string command);
    void putCmd(string &commandline, string command);    
public:
    IO(char* argv[]);
    void run();
};
