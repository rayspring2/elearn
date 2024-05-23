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
const string IO::PERSONALPAGE_STR = "personal_page";


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
        if(!isempty(commandline))
            throw runtime_error(BADREQUEST);    
        utms.printCourseList();
    }
    if( command == PERSONALPAGE_STR ){
        int id = stoi(findGetValue(ID_FLAG, commandline));
                //cerr << "eneteredpersnoalkjf\n";

        utms.getPersonalPage(id);
    }
    else
        throw runtime_error(NOTFOUND);
}

void IO::postCmd(string &commandline, string command){
    if(command == LOGIN_STR){
        int id = stoi(findGetValue(ID_FLAG, commandline)) ;
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
    else{
        throw runtime_error(NOTFOUND);
    }
}


void IO::deleteCmd(string &commandline, string command){
    if(command == POST_STR){
        int id = stoi(findGetValue(ID_FLAG, commandline)) ;
        if(!isempty(commandline))
            throw runtime_error(BADREQUEST);
        utms.deletePost(id);
    }
}
void IO::putCmd(string &commandline, string command){
    
}

