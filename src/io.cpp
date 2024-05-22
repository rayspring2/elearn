#include "IO.hpp"

void IO::run( char* argv[]){
    utms.readData(argv);
    string commandline;
    while(getline(cin, commandline)){
        try{
            string cmd_type = divString( commandline , CMD_SEPERATOR );
            string command = divString( commandline , CMD_SEPERATOR );
            string delim = divString( commandline , CMD_SEPERATOR );
            if(delim != REQUESTDELIMITER)
                throw runtime_error(BADREQUEST);
            if(cmd_type == GET)
                getCmd(commandline, command);
            else if(cmd_type == PUT)
                putCmd(commandline, command);
            else if(cmd_type == POST)
                postCmd(commandline, command);
            else if(cmd_type == DELETE)
                deleteCmd(commandline, command);
            else
                throw runtime_error(BADREQUEST);
            cout << OK;
        }
        catch(const runtime_error& e){
            cout << e.what();
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
        utms.login(getIdPassword(commandline));
    }
    else if (command == LOGOUT_STR){
        utms.logout(commandline);
    }
    else{
        throw runtime_error(NOTFOUND);
    }
}


LoginInfo IO::getIdPassword(string &commandline){
    string type;
    string value;
    LoginInfo login_info;
    for(int i = 0; i < 2; i++){
        type = divString(commandline, CMD_SEPERATOR );
        if(type == ID_FLAG){
            value = divString(commandline, CMD_SEPERATOR );
            try{
                login_info.id = stoi (value);
            }
            catch(const runtime_error& e){
                throw runtime_error(BADREQUEST);
            }
        }
        else if(type == PASSWORD_FLAG)
            login_info.password = divString(commandline, CMD_SEPERATOR );
        else
            throw runtime_error(BADREQUEST);
    }
    if(!commandline.empty())
        throw runtime_error(BADREQUEST);
    return login_info;
}
void IO::deleteCmd(string &commandline, string command){

}
void IO::putCmd(string &commandline, string command){
    
}

