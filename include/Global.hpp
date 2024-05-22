#pragma once

#include <iostream>
#include <sstream>
#include <istream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <stdexcept>
#include <exception>
using namespace std;

const string OK = "OK\n";
const string EMPTYLIST = "Empty\n";
const string NOTFOUND = "Not Found\n";
const string BADREQUEST = "Bad Request\n";
const string PERMISSIONDENIED = "Permission Denied\n";

const char CMD_SEPERATOR = ' '; 

struct LoginInfo{
    int id;
    string password;
};
vector<vector<string>> readCSVLine( string line );
string divString( string &input , char delim);