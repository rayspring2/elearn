#include "IO.hpp"


const string IO::GET = "GET";
const string IO::PUT = "PUT";
const string IO::POST = "POST";
const string IO::DELETE = "DELETE"; 
const string IO::REQUESTDELIMITER = "?";
const string IO::LOGIN_STR = "login";
const string IO::LOGOUT_STR = "logout";
const string IO::POST_STR = "post";
const string IO::ID_FLAG = "id";
const string IO::PASSWORD_FLAG = "password";
const string IO::TITLE_FLAG = "title";
const string IO::MESSAGE_FLAG = "message";
const string IO::COURSES_STR = "courses";


void IO::run( char* argv[]){
    utms.readData(argv);
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
        if(!commandline.empty())
            throw runtime_error(BADREQUEST);    
        utms.printCourseList();
    }
}

void IO::postCmd(string &commandline, string command){
    if(command == LOGIN_STR){
        utms.login(stoi(findGetValue(ID_FLAG, commandline)) , findGetValue(PASSWORD_FLAG, commandline));
    }
    else if(command == LOGOUT_STR){
        utms.logout(commandline);
    }
    else if(command == POST_STR){
        utms.addPost(findGetValue(TITLE_FLAG, commandline), findGetValue(MESSAGE_FLAG, commandline) );
    }
    else{
        throw runtime_error(NOTFOUND);
    }
}


void IO::deleteCmd(string &commandline, string command){

}
void IO::putCmd(string &commandline, string command){
    
}

