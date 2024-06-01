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
const int MAX_ID_LENGTH = 10;

const char SPACE =' ';
const char QUATATION = '\"';
const char NEXTLINE = '\n';
const char COMMA = ',';
const char SEMICOLON = ';';
const char COLON = ':';
const char DASH = '-';
const char DEFALUT_CMD_DELIM = SPACE; 
const char DEFAULT_MESSAGE_DELIM = QUATATION;
const string EMPTYPIC = "";

vector<vector<string>> readCSVLine( string line );
string divString( string &input , char delim = DEFALUT_CMD_DELIM , char message_delim = DEFAULT_MESSAGE_DELIM);
string findGetValue( string word , string &str , char delim = DEFALUT_CMD_DELIM , char message_delim = DEFAULT_MESSAGE_DELIM);
bool isempty(string s , char delim = DEFALUT_CMD_DELIM);
int getNatrualNumb(string s);
int getWholeNumb(string s);
bool stringContainsSeperateWord(string word, string input);

