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
#include <exception>>
using namespace std;

const string OKINPUT = "OK\n";
const string EMPTYLIST = "Empty\n";
const string NOTFOUND = "Not Found\n";
const string BADREQUEST = "Bad Request\n";
const string PERMISSIONDENIED = "Permission Denied\n";


vector<vector<string>> readCSVLine( string line );