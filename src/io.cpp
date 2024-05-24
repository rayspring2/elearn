#include "IO.hpp"


const string IO::GET = "GET";
const string IO::PUT = "PUT";
const string IO::POST = "POST";
const string IO::DELETE = "DELETE"; 
const string IO::REQUESTDELIMITER = "?";

const string IO::LOGIN_STR = "login";
const string IO::LOGOUT_STR = "logout";
const string IO::POST_STR = "post";
const string IO::COURSES_STR = "courses";
const string IO::COURSE_OFFER_STR = "course_offer";
const string IO::PERSONALPAGE_STR = "personal_page";
const string IO::CONNECT_STR = "connect";
const string IO::NOTIFICATION_STR = "notification";
const string IO::MYCOURSES_STR = "my_course";

const string IO::ID_FLAG = "id";
const string IO::POSTID_FLAG = "post_id";
const string IO::PASSWORD_FLAG = "password";
const string IO::TITLE_FLAG = "title";
const string IO::MESSAGE_FLAG = "message";
const string IO::COURSE_ID_FLAG = "course_id";
const string IO::PROFESSOR_ID_FLAG = "professor_id";
const string IO::CAPACITY_FLAG = "capacity";
const string IO::TIME_FLAG = "time";
const string IO::CLASS_NUMBER_FLAG = "class_number";
const string IO::EXAM_DATE_FLAG = "exam_date";

IO::IO(char* argv[]){
    utms.readData(argv);
}
void IO::run(){
    string commandline;
    while(getline(cin, commandline)){
        try{
            string cmd_type = divString( commandline );
            string command = divString( commandline );
            string delim = divString( commandline );
            if(delim != REQUESTDELIMITER)
                throw runtime_error(BADREQUEST);
            if(cmd_type == GET)
                getCmd(commandline, command);
            else{
                if(cmd_type == PUT)
                    putCmd(commandline, command);
                else if(cmd_type == POST)
                    postCmd(commandline, command);
                else if(cmd_type == DELETE)
                    deleteCmd(commandline, command);
                else
                    throw runtime_error(BADREQUEST);
                cout << OK;
            }
        }
        catch(const runtime_error& e){
            cout << e.what();
        }  
        catch(const invalid_argument& e){
            cout << BADREQUEST;
        }
    }
}



void IO::getCmd(string &commandline, string command){
    if( command == COURSES_STR ){
        if(!isempty(commandline))
            throw runtime_error(BADREQUEST);    
        utms.printCourseList();
    }
    else if( command == PERSONALPAGE_STR ){
        int id = stoi(findGetValue(ID_FLAG, commandline));
        if(!isempty(commandline))
            throw runtime_error(BADREQUEST);  
        utms.getPersonalPage(id);
    }
    else if( command == POST_STR){
        int user_id = stoi(findGetValue(ID_FLAG, commandline));
        int post_id = stoi(findGetValue(POSTID_FLAG, commandline));
        if(!isempty(commandline))
            throw runtime_error(BADREQUEST);  
        utms.viewPost(user_id, post_id);
    }
    else if( command == NOTIFICATION_STR){
        if(!isempty(commandline))
            throw runtime_error(BADREQUEST); 
        utms.viewNotification();  
    }
    else if(command == MYCOURSES_STR){
        if(!isempty(commandline))
            throw runtime_error(BADREQUEST); 
        utms.viewMyCourses();
    }
    else
        throw runtime_error(NOTFOUND);
}

void IO::postCmd(string &commandline, string command){
    if(command == LOGIN_STR){
        int id = stoi(findGetValue(ID_FLAG, commandline));
        string password = findGetValue(PASSWORD_FLAG, commandline);
        if(!isempty(commandline))
            throw runtime_error(BADREQUEST);
        utms.login(id, password);
    }
    else if(command == LOGOUT_STR){
        if( !isempty(commandline) )
            throw runtime_error(BADREQUEST);
        utms.logout();
    }
    else if(command == POST_STR){
        string title = findGetValue(TITLE_FLAG, commandline);
        string message = findGetValue(MESSAGE_FLAG, commandline);
        if( !isempty(commandline) )
            throw runtime_error(BADREQUEST);
        utms.addPost( title, message );
    }
    else if(command == CONNECT_STR){
        int id = stoi(findGetValue(ID_FLAG, commandline));
        if( !isempty(commandline) )
            throw runtime_error(BADREQUEST);
        utms.connect(id);
    }
    else if(command == COURSE_OFFER_STR){
        int course_id = stoi(findGetValue(COURSE_ID_FLAG, commandline));
        int professor_id = stoi(findGetValue(PROFESSOR_ID_FLAG, commandline));
        int capacity = stoi(findGetValue(CAPACITY_FLAG, commandline));
        Time time(findGetValue(TIME_FLAG , commandline));
        Date exame_date(findGetValue(EXAM_DATE_FLAG , commandline));
        int class_numebr = stoi(findGetValue(CLASS_NUMBER_FLAG , commandline));
        if( !isempty(commandline) )
            throw runtime_error(BADREQUEST);
        utms.courseOffer(course_id, professor_id, capacity, time, exame_date, class_numebr );
    }
    else{
        throw runtime_error(NOTFOUND);
    }
}


void IO::deleteCmd(string &commandline, string command){
    if(command == POST_STR){
        int id = stoi(findGetValue(ID_FLAG, commandline));
        if(!isempty(commandline))
            throw runtime_error(BADREQUEST);
        utms.deletePost(id);
    }
    else if(command == MYCOURSES_STR){
        int id = stoi(findGetValue(ID_FLAG, commandline));
        utms.deleteCourse(id);   
    }
    else{
        throw runtime_error(NOTFOUND);
    }
}
void IO::putCmd(string &commandline, string command){
    if(command == MYCOURSES_STR ){
        int id = stoi(findGetValue(ID_FLAG, commandline));
        if(!isempty(commandline))
            throw runtime_error(BADREQUEST);
        utms.addStudentCourse(id);
    }
    else{
        throw runtime_error(NOTFOUND);
    }
}


