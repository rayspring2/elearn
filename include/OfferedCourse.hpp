#pragma once
#include "Global.hpp"
#include "Course.hpp"
#include "Time.hpp"
#include "Date.hpp"
#include "Professor.hpp"
class OfferedCourse{
private:   
    Course* course; 
    Professor* professor; 
    int capacity;
    Time time;
    Date exame_date;
    int class_numebr;
public:
    OfferedCourse(Course* course, Professor* professor, int capacity,Time time, Date exame_date, int class_numebr);
    int getProfessorId();
    bool hasTimeConflict(OfferedCourse* course);
};