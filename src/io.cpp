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
const string IO::MYCOURSES_STR = "my_courses";
const string IO::PROFILE_PHOTO_STR = "profile_photo";
const string IO::COURSE_POST_STR = "course_post";
const string IO::COURSE_CHANNEL_STR = "course_channel";
const string IO::TA_FORM_STR = "ta_form";

const string IO::ID_FLAG = "id";
const string IO::PHOTO_FLAG = "photo";
const string IO::POSTID_FLAG = "post_id";
const string IO::PASSWORD_FLAG = "password";
const string IO::TITLE_FLAG = "title";
const string IO::MESSAGE_FLAG = "message";
const string IO::IMAGE_FLAG = "image";
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
                output.push_back(OK);
            }
        }
        catch(const runtime_error& e){
            output.push_back(e.what());
        }  
        printOutput();
    }
}


void IO::printOutput(){
    for(string s : output ){
        cout << s << std::flush;
    }
    output.clear(); 
}


void IO::getCmd(string &commandline, string command){
    if(find(getcommands.begin(), getcommands.end(), command ) == getcommands.end())
        throw runtime_error(NOTFOUND);
    
    if( command == COURSES_STR )
        getCourse(commandline);
    
    else if( command == PERSONALPAGE_STR )
        getPersonalPage(commandline);

    else if( command == POST_STR)
        getPost(commandline);
    
    else if( command == NOTIFICATION_STR)
        getNotification(commandline);
    
    else if(command == MYCOURSES_STR)
        getMyCourses(commandline);
    
    else if(command == COURSE_CHANNEL_STR)
        getCourseChannel(commandline);
        
    
}


void IO::postCmd(string &commandline, string command){
    if(find(postcommands.begin(), postcommands.end(), command ) == postcommands.end())
        throw runtime_error(NOTFOUND);

    if(command == LOGIN_STR)
        postLogin(commandline);
    
    else if(command == LOGOUT_STR)
        postLogout(commandline);
    
    else if(command == POST_STR)
        postPost(commandline);
    
    else if(command == CONNECT_STR)
        postConnect(commandline);

    else if(command == COURSE_OFFER_STR)
        postCourseOffer(commandline);
    
    else if(command == PROFILE_PHOTO_STR)
        postProfilePhoto(commandline);
    
    else if(command == COURSE_POST_STR)
        postCoursePost(commandline);
    
    else if (command == TA_FORM_STR)
        postTAForm(commandline);
    
    
}

void IO::deleteCmd(string &commandline, string command){
    if(find(deletecommands.begin(), deletecommands.end(), command ) == deletecommands.end())
        throw runtime_error(NOTFOUND);

    if(command == POST_STR)
        deletePost(commandline);
    
    else if(command == MYCOURSES_STR)
          deleteMycourse(commandline); 
}

void IO::putCmd(string &commandline, string command){
    if(find(putcommands.begin(), putcommands.end(), command ) == putcommands.end())
        throw runtime_error(NOTFOUND);
    
    if(command == MYCOURSES_STR )
        putMyCourse(commandline);
}





void IO::getCourse(string &commandline){
    if(!utms.isLoggedIn() || utms.userIsAdmin())
            throw runtime_error(PERMISSIONDENIED);

    if(isempty(commandline))   
        utms.printCourseList(output);
    else{
        int id = getNatrualNumb(findGetValue(ID_FLAG, commandline));
        if(!isempty(commandline))
            throw runtime_error(BADREQUEST);
        utms.printCourse(id, output); 
    }
}

void IO::getPersonalPage(string &commandline){
    if(!utms.isLoggedIn() || utms.userIsAdmin()){
        throw runtime_error(PERMISSIONDENIED);
    }   
    int id = getWholeNumb(findGetValue(ID_FLAG, commandline));

    if(!isempty(commandline))
        throw runtime_error(BADREQUEST); 
    utms.getPersonalPage(id, output);
}

void IO::getPost(string &commandline){
    if(!utms.isLoggedIn() || utms.userIsAdmin())
            throw runtime_error(PERMISSIONDENIED);   
    int user_id = getWholeNumb(findGetValue(ID_FLAG, commandline));
    int post_id = getNatrualNumb(findGetValue(POSTID_FLAG, commandline));
    if(!isempty(commandline))
        throw runtime_error(BADREQUEST);  
    utms.viewPost(user_id, post_id, output);
}

void IO::getNotification(string &commandline){
    if(!utms.isLoggedIn() || utms.userIsAdmin())
            throw runtime_error(PERMISSIONDENIED);
    if(!isempty(commandline))
        throw runtime_error(BADREQUEST); 
    utms.viewNotification(output); 
}

void IO::getMyCourses(string &commandline){
    if(!utms.userIsStudent())
        throw runtime_error(PERMISSIONDENIED);
    if(!isempty(commandline))
        throw runtime_error(BADREQUEST); 
    utms.viewMyCourses(output);
}

void IO::getCourseChannel(string &commandline){
    if(!utms.isLoggedIn() || utms.userIsAdmin())
        throw runtime_error(PERMISSIONDENIED);
    int id = getWholeNumb(findGetValue(ID_FLAG, commandline));
    if(!isempty(commandline))
        utms.viewCourseChannel(id, output);    
    else{
        int post_id = getNatrualNumb(findGetValue(POSTID_FLAG, commandline));
        if(!isempty(commandline))
            throw runtime_error(BADREQUEST);
        utms.ViewCourseChannelPost(id, post_id, output);
    }
}








void IO::postLogin(string &commandline){
    if(utms.isLoggedIn())
            throw runtime_error(PERMISSIONDENIED);
    int id = getWholeNumb(findGetValue(ID_FLAG, commandline));
    string password = findGetValue(PASSWORD_FLAG, commandline);
    if(!isempty(commandline))
        throw runtime_error(BADREQUEST);
    utms.login(id, password);
}

void IO::postLogout(string &commandline){
    if(!utms.isLoggedIn())
            throw runtime_error(PERMISSIONDENIED);
    if( !isempty(commandline) )
        throw runtime_error(BADREQUEST);
    utms.logout();
}

void IO::postPost(string &commandline){
    if(!utms.isLoggedIn())
            throw runtime_error(PERMISSIONDENIED);
    string title = findGetValue(TITLE_FLAG, commandline);
    string message = findGetValue(MESSAGE_FLAG, commandline);
    string image_path = EMPTYPIC;
    if(stringContainsSeperateWord(IMAGE_FLAG, commandline))
        image_path = findGetValue(IMAGE_FLAG, commandline);
    
    if( !isempty(commandline) )
        throw runtime_error(BADREQUEST);
    utms.addPost( title, message, image_path );
}

void IO::postConnect(string &commandline){
    if(!utms.isLoggedIn() || utms.userIsAdmin())
            throw runtime_error(PERMISSIONDENIED);
    int id = getNatrualNumb(findGetValue(ID_FLAG, commandline));
    if( !isempty(commandline) )
        throw runtime_error(BADREQUEST);
    utms.connect(id);
}

void IO::postCourseOffer(string &commandline){
    if(!utms.userIsAdmin())
        throw runtime_error(PERMISSIONDENIED);
    int course_id = getNatrualNumb(findGetValue(COURSE_ID_FLAG, commandline));
    int professor_id = getNatrualNumb(findGetValue(PROFESSOR_ID_FLAG, commandline));
    int capacity = getNatrualNumb(findGetValue(CAPACITY_FLAG, commandline));
    Time time(findGetValue(TIME_FLAG , commandline));
    Date exame_date(findGetValue(EXAM_DATE_FLAG , commandline));
    int class_numebr = getNatrualNumb(findGetValue(CLASS_NUMBER_FLAG , commandline));
    if( !isempty(commandline) )
        throw runtime_error(BADREQUEST);
    utms.courseOffer(course_id, professor_id, capacity, time, exame_date, class_numebr );
}

void IO::postProfilePhoto(string &commandline){
    if(!utms.isLoggedIn() || utms.userIsAdmin())
        throw runtime_error(PERMISSIONDENIED);
    string profile_photo_path = findGetValue(PHOTO_FLAG, commandline);
    if( !isempty(commandline) )
        throw runtime_error(BADREQUEST);
    utms.setProfilePhoto(profile_photo_path);
}

void IO::postCoursePost(string &commandline){
    if(!utms.isLoggedIn() || utms.userIsAdmin())
        throw runtime_error(PERMISSIONDENIED);
    int offered_course_id = getNatrualNumb(findGetValue(ID_FLAG, commandline));
    string title = findGetValue(TITLE_FLAG, commandline);
    string message = findGetValue(MESSAGE_FLAG, commandline);
    
    string image_path = EMPTYPIC;
    if(stringContainsSeperateWord(IMAGE_FLAG, commandline))
        image_path = findGetValue(IMAGE_FLAG, commandline);
    if( !isempty(commandline) )
        throw runtime_error(BADREQUEST);
    utms.addCoursePost(offered_course_id, title, message, image_path);
}

void IO::postTAForm(string &commandline){
    if(!utms.userIsProfessor())
        throw runtime_error(PERMISSIONDENIED);
    
    int course_id = getNatrualNumb(findGetValue(COURSE_ID_FLAG, commandline));
    string message = findGetValue(MESSAGE_FLAG, commandline);
    if( !isempty(commandline) )
        throw runtime_error(BADREQUEST);
    utms.addTAForm(course_id, message);

}






void IO::deletePost(string &commandline){
    if(!utms.isLoggedIn() )
        throw runtime_error(PERMISSIONDENIED);
    int id = getNatrualNumb(findGetValue(ID_FLAG, commandline));
    if(!isempty(commandline))
        throw runtime_error(BADREQUEST);
    utms.deletePost(id);
}
void IO::deleteMycourse(string &commandline){
    if(!utms.userIsStudent())
            throw runtime_error(PERMISSIONDENIED);
        int id = getNatrualNumb(findGetValue(ID_FLAG, commandline));
        utms.deleteCourse(id); 
}


void IO::putMyCourse(string &commandline){
    if(!utms.userIsStudent())
        throw runtime_error(PERMISSIONDENIED);
    int id = getNatrualNumb(findGetValue(ID_FLAG, commandline));
    if(!isempty(commandline))
        throw runtime_error(BADREQUEST);
    utms.addStudentCourse(id);   
}




