#include "OfferedCourse.hpp"

OfferedCourse::OfferedCourse(int id, Course* course, int professor_id, 
string professor_name, int capacity,Time time, Date exame_date, int class_numebr):

id(id), course(course), professor_id(professor_id), professor_name(professor_name), 
capacity(capacity), time(time), exame_date(exame_date), class_numebr(class_numebr)  {

    addProfessor(professor_id);
}

void OfferedCourse::addStudent(int id){
    participants.push_back(Participant(id, STUDENT ));
}
void OfferedCourse::addProfessor(int id){
    participants.push_back(Participant(id, PROFESSOR ));
}
void OfferedCourse::addTA(int id){
    participants.push_back(Participant(id, TA ));
}

bool OfferedCourse::isTA(int id){
    auto it = find_if(participants.begin(), participants.end(), [id](Participant &p){
        return p.id == id;
    });
    return (*it).role == TA;
}

bool OfferedCourse::isProfessor(int id){
    auto it = find_if(participants.begin(), participants.end(), [id](Participant &p){
        return p.id == id;
    });
    return (*it).role == PROFESSOR;
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

string OfferedCourse::getName(){
    return course->getName();
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
    participants.erase(find_if(participants.begin(), participants.end(), [id](Participant &p){
        return p.id == id;
    }));
}

void OfferedCourse::addPost(int sender_id, string title, 
string message, string image_path){
    if(!isAParticipant(sender_id))
        throw runtime_error(PERMISSIONDENIED);
    if(!isTA(sender_id) && !isProfessor(sender_id))
        throw runtime_error(PERMISSIONDENIED);
        
    cnt_channel_posts++;
    ChannelPost * new_channel_post = new ChannelPost(sender_id, cnt_channel_posts, title, message, image_path );
    channel_posts.push_back(new_channel_post);
}

bool OfferedCourse::isAParticipant(int id){
    for(auto i : participants){
        if(id == i.id)
            return 1;
    }
    return 0;
}

string OfferedCourse::getChannelPrint(vector<User*> &users){
    string outstr = getDetailedPrint();
    for( int i = channel_posts.size() - 1; i >= 0  ; i-- ){
        ChannelPost* p = channel_posts[i];
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
    QUATATION + post->getTitle() + QUATATION + SPACE +
    QUATATION + post->getMessage() + QUATATION + NEXTLINE;
    
    return outstr;
}

ChannelPost* OfferedCourse::findPost(int post_id){
    auto it = find_if(channel_posts.begin(), channel_posts.end(), [post_id](ChannelPost* &c){
       return c->getId() == post_id ; 
    });
    
    return *it;
}

Notification* OfferedCourse::createNotification(string message){
    return new Notification(course->getId(), course->getName(), message);
}

vector<int> OfferedCourse::getParticipantIds(){
    vector<int> output;
    for(Participant p : participants){
        output.push_back(p.id);
    }
    return output;
}







