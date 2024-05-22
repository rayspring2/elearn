#pragma once
#include "Global.hpp"
#include "System.hpp"
const string GET = "GET";
const string PUT = "PUT";
const string POST = "POST";
const string DELETE = "DELETE";

const string REQUESTDELIMITER = "?";
const string LOGIN_STR = "login";
const string LOGOUT_STR = "logout";
const string ID_FLAG = "id";
const string PASSWORD_FLAG = "password";
const string COURSES_STR = "courses";

class IO{
private:
    System utms;
    void getCmd(string &commandline, string command); //output al list or with id ouput details
    void postCmd(string &commandline, string command);
    void deleteCmd(string &commandline, string command);
    void putCmd(string &commandline, string command);
    LoginInfo getIdPassword(string &commandline);
    
public:
    void run(char* argv[]);
};
