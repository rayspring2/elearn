#pragma once
#include "Global.hpp"
#include "Course.hpp"
#include "Time.hpp"
#include "Date.hpp"
#include "ChannelPost.hpp"
#include "User.hpp"
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
    vector<int> participant_ids;
    int cnt_channel_posts = 0;
    vector<ChannelPost*> channel_posts;
    bool isAParticipant(int id);

public:
    OfferedCourse(int id, Course* course,int professor_id, string professor_name, int capacity,Time time, Date exame_date, int class_numebr);
    void addParticipant(int id);
    int getProfessorId();
    bool hasTimeConflict(OfferedCourse* course);
    int getId();
    Course* getCourse();
    bool hasExamDayConflict(OfferedCourse* course);
    string getShortPrint();
    string getDetailedPrint();
    void deleteParticipant(int id);
    vector<int> getParticipantIds();
    void addPost(int sender_id, string title, string message, string image_path);
    string getChannelPrint(vector<User*> users);

};