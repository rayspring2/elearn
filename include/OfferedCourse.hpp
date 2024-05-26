#pragma once
#include "Global.hpp"
#include "Course.hpp"
#include "Time.hpp"
#include "Date.hpp"
class OfferedCourse{
private:   
    int id;
    Course* course;
    int professor_id;
    string professor_name;
    int capacity;
    Time time;
    Date exame_date;
    int class_numebr;
public:
    OfferedCourse(int id, Course* course,int professor_id, string professor_name, int capacity,Time time, Date exame_date, int class_numebr);
    int getProfessorId();
    bool hasTimeConflict(OfferedCourse* course);
    int getId();
    Course* getCourse();
    bool hasExamDayConflict(OfferedCourse* course);
    void shortPrint(vector<string> &output);
    void detailedPrint(vector<string> &output);

};