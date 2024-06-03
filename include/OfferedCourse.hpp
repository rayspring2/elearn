#pragma once
#include "Global.hpp"
#include "Course.hpp"
#include "Time.hpp"
#include "Date.hpp"
#include "ChannelPost.hpp"
#include "User.hpp"
enum Role{
    PROFESSOR, STUDENT, TA
};

struct Participant{
    Role role;
    int id;
    Participant(int id, Role role): id(id), role(role){}
    string getrole(){
        if(role == PROFESSOR)
            return "professor";
        else if(role == STUDENT)
            return "student";
        else
            return "ta";
    }
};

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
    vector<Participant> participants;
    int cnt_channel_posts = 0;
    vector<ChannelPost*> channel_posts;
    ChannelPost* findPost(int post_id);

public:
    OfferedCourse(int id, Course* course,int professor_id, string professor_name, int capacity,Time time, Date exame_date, int class_numebr);
    bool isAParticipant(int id);
    int getProfessorId();
    bool hasTimeConflict(OfferedCourse* course);
    int getId();
    string getName();
    Course* getCourse();
    bool hasExamDayConflict(OfferedCourse* course);
    string getShortPrint();
    string getDetailedPrint();
    void deleteParticipant(int id);
    void addPost(int sender_id, string title, string message, string image_path);
    string getChannelPrint(vector<User*> &users);
    string getChannelPostPrint(int post_id, vector<User*> &users);
    void addStudent(int id);
    void addProfessor(int id);
    void addTA(int id);
    bool isTA(int id);
    bool isProfessor(int id);
    Notification* createNotification(string message);
    vector<int> getParticipantIds();
    
};