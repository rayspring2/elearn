#pragma once
#include "Global.hpp"
#include "User.hpp"
#include "Major.hpp"
#include "OfferedCourse.hpp"
#include "TAFormPost.hpp"
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
    static const string NEW_FORM_STR;
private:
    Major* major; 
    ProfPos position; 
    vector<OfferedCourse*> courses;
public:
    Professor(int id, string name, Major* major, string position, string password);
    void setPositionByString(string pos);
    string getPositionAsString();
    int getMajorId();
    string getPrint();
    void getPersonalPage(vector<string> &output);
    void addCourse(OfferedCourse* course);
    void addTAForm(OfferedCourse* course, string message);
    TAFormPost* findTaForm(int id);
};