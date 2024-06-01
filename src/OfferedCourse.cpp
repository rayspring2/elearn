#include "OfferedCourse.hpp"

OfferedCourse::OfferedCourse(int id, Course* course, int professor_id, 
string professor_name, int capacity,Time time, Date exame_date, int class_numebr):
id(id), course(course), professor_id(professor_id), professor_name(professor_name), 
capacity(capacity), time(time), exame_date(exame_date), class_numebr(class_numebr){
    addParticipant(professor_id);
}

void OfferedCourse::addParticipant(int id){
    participant_ids.push_back(id);
}
int OfferedCourse::getProfessorId(){
    return professor_id;
}

bool OfferedCourse::hasTimeConflict(OfferedCourse* course){
    return time.hasConflict(course->time);
}
bool OfferedCourse::hasExamDayConflict(OfferedCourse* course){
    return exame_date.isEqual(course -> exame_date);
}
int OfferedCourse::getId(){
    return id;
}
Course* OfferedCourse::getCourse(){
    return course;
}

void OfferedCourse::shortPrint(vector<string> &output){
    string outstr = to_string(id) + SPACE + course->getName() + SPACE + to_string(capacity) + SPACE + professor_name + NEXTLINE;
    output.push_back(outstr);
}
void OfferedCourse::detailedPrint(vector<string> &output){
    string outstr =  to_string(id) + SPACE + course->getName() + SPACE + to_string(capacity) + SPACE +
    professor_name + SPACE + time.getPrint() + SPACE + exame_date.getPrint() +
    SPACE + to_string(class_numebr) + NEXTLINE;
    output.push_back(outstr);

}

void OfferedCourse::deleteParticipant(int id){
    participant_ids.erase(find(participant_ids.begin(), participant_ids.end(), id));
}

vector<int> OfferedCourse::getParticipantIds(){
    return participant_ids;
}

void OfferedCourse::addPost(int sender_id, string title, 
string message, string image_path){
    if(!isAParticipant(sender_id)){
        throw runtime_error(PERMISSIONDENIED);
    }
    cnt_channel_posts++;
    ChannelPost * new_channel_post = new ChannelPost(sender_id, cnt_channel_posts, title, message, image_path );
    channel_posts.push_back(new_channel_post);
}

bool OfferedCourse::isAParticipant(int id){
    for(int i : participant_ids){
        if(id == i)
            return 1;
    }
    return 0;
}

