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

string OfferedCourse::getShortPrint(){
    string outstr = to_string(id) + SPACE + course->getName() + SPACE + to_string(capacity) + SPACE + professor_name + NEXTLINE;
    return outstr;
}
string OfferedCourse::getDetailedPrint(){
    string outstr =  to_string(id) + SPACE + course->getName() + SPACE + to_string(capacity) + SPACE +
    professor_name + SPACE + time.getPrint() + SPACE + exame_date.getPrint() +
    SPACE + to_string(class_numebr) + NEXTLINE;
    return outstr;
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

string OfferedCourse::getChannelPrint(vector<User*> &users){
    string outstr = getDetailedPrint();
    for(ChannelPost* p : channel_posts ){
        int sender_id = p->getSenderId();
        auto user = find_if(users.begin(), users.end(), [sender_id](User* &u){
           return u->getId() == sender_id; 
        } );
        
        outstr += to_string(p->getId()) + SPACE +
        (*user)->getName() + SPACE +
        QUATATION + p->getTitle() + QUATATION + NEXTLINE;
    }
    return outstr;
}

string OfferedCourse::getChannelPostPrint(int post_id, vector<User*> &users){
    string outstr = getDetailedPrint();
    ChannelPost* post = findPost(post_id);
    int sender_id = post->getSenderId();
    auto user = find_if(users.begin(), users.end(), [sender_id](User* &u){
        return u->getId() == sender_id; 
    } );
    
    outstr += to_string(post->getId()) + SPACE +
    (*user)->getName() + SPACE +
    QUATATION + post->getTitle() + QUATATION +
    QUATATION + post->getMessage() + QUATATION + NEXTLINE;
    
    return outstr;
}

ChannelPost* OfferedCourse::findPost(int post_id){
    auto it = find_if(channel_posts.begin(), channel_posts.end(), [post_id](ChannelPost* &c){
       return c->getId() == post_id ; 
    });
    
    return *it;
}





