#pragma once
#include "Global.hpp"
#include "User.hpp"

const string INSTRUCTOR_STR = "instructor";
const string ASSISTANTPROF_STR = "assistant professor";
const string ASSOCIATEPROF_STR =  "associate professor";
const string PROF_STR = "professor";
enum ProfPos{
    INSTRUCTOR,
    ASSISTANTPROF,
    ASSOCIATEPROF,
    PROF
};

//instructor، assistant professor، associate professor, professor
class Professor : public User{
private:
    int major_id; 
    ProfPos position; 
public:
    Professor(int id, string name, int major_id, string position, string password);
    void setPositionByString(string pos);
    string getPositionAsString();
    void print();
};