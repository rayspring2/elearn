#include "System.hpp"

void System::run(){
    stringstream commandline;
    while(inputCommand(commandline)){
        string cmd_type;
        commandline >> cmd_type;
        string command;
        char delim;
        commandline >> command >> delim;
        if(delim != REQUESTDELIMITER){
            cerr << BADREQUEST;
            continue;
        }

        if(cmd_type == GETCMD){
            try{
                getCmd(commandline, command);
            }
            catch(const runtime_error& e){
                cout << e.what();
                continue;
            }
        }
        else if(cmd_type == PUTCMD)
            putCmd(commandline, command);
        
        else if(cmd_type == POSTCMD){
            try{
                postCmd(commandline, command);
            }
            catch(const runtime_error& e){
                cout << e.what();
                continue;
            }
        }
        
        else if(cmd_type == DELETECMD)
            deleteCmd(commandline, command);
        
        else
            cerr << BADREQUEST;
        
    }
}

istream& System::inputCommand(stringstream &command){
    string input;
    istream& cnt = getline(cin, input);
    command = stringstream(input);
    return cnt;
}

void System::readData( ifstream &majors_file, ifstream &courses_file, ifstream &professors_file, ifstream &students_file){
    readMajorData(majors_file);
    readCourseData(courses_file);
    readProfessorData(professors_file);
    readStudentData(students_file);
}

void System::readMajorData(ifstream &major_file){
    string line;
    getline( major_file, line );
    vector<vector<string>> input;
    while(getline(major_file , line)){
        input = readCSVLine( line );
        Major* new_major = new Major( stoi(input[0][0]) , input[1][0] );
        addMajor(new_major);
    }
}


void System::readCourseData(ifstream &course_file){
    string line;
    getline( course_file, line );
    vector<vector<string>> input;
    
    while(getline(course_file , line)) {
        input = readCSVLine( line );
        vector<int> majors_id;
        
        transform(input[4].begin(), input[4].end(), back_inserter(majors_id),
               [](const string& str) { return stoi(str); });
               
        Course* new_course = new Course( stoi( input[0][0] ) , input[1][0],
        stoi(input[2][0]), stoi(input[3][0]), majors_id);
        addCourse(new_course);
    }
}


void System::readProfessorData(ifstream &professor_file){
    string line;
    getline( professor_file, line );
    vector<vector<string>> input;
    
    while(getline(professor_file , line)) {
        input = readCSVLine( line );
        Professor* new_professor = new Professor( stoi( input[0][0] ), input[1][0],
        stoi(input[2][0]), input[3][0], input[4][0] );
        addUser(new_professor);
    }
}


void System::readStudentData(ifstream &student_file){
    string line;
    getline( student_file, line );
    vector<vector<string>> input;
    
    while(getline(student_file , line)) {
        input = readCSVLine( line );

        Student* new_student = new Student( stoi( input[0][0] ), input[1][0],
        stoi(input[2][0]), stoi(input[3][0]), input[4][0] );
        addUser(new_student);
    }
}


void System::getCmd(stringstream &commandline, string command){
    if( command == COURSES_STR ){
        if(commandline.str().empty())
            printCourseList();   
    }

}
void System::printCourseList(){
    
}
void System::postCmd(stringstream &commandline, string command){
    if(command == LOGIN_STR){
        login(commandline);
    }
    else if (command == LOGOUT_STR){
        logout(commandline);
    }
    else{
        throw runtime_error(NOTFOUND);
    }
}

void System::login(stringstream &commandline){
    int id;
    string password;
    getIdPassword( commandline, id, password );

    if(isLoggedIn()){
        throw runtime_error(PERMISSIONDENIED);
    }

    User* user = USER_NOTFPUND;
    for(User* u : users){
        if( u->idIsEqualTo( id ) ){
            user = u;
            break;
        }
    }
    if(user == USER_NOTFPUND){
        throw runtime_error(NOTFOUND); 
    }
    if(user->PasswordisEqualTo(password)){
        throw runtime_error(PERMISSIONDENIED); 
    }

    current_user = user;
    cout << OKINPUT;

}

void System::getIdPassword(stringstream &commandline , int &id , string &password){
    string type;
    string value;
    for(int i = 0; i < 2; i++){
        commandline >> type;
        if(type == ID_FLAG){
            commandline >> value;
            try{
                id = stoi (value);
            }
            catch(const invalid_argument& e){
                throw runtime_error(BADREQUEST);
            }
        }
        else if(type == PASSWORD_FLAG)
            commandline >> password;
        else
            throw runtime_error(BADREQUEST);
    }
}

void System::logout(stringstream &commandline){
    if( !commandline.str().empty() ){
        // error ! should be empty
        exit(-1);
    }
    if(!isLoggedIn()){
        // permission denied already loged out
        exit(-1);
    }
    current_user = NOT_LOGIN;
}

bool System::isLoggedIn(){
    return !(current_user == nullptr);
}
void System::deleteCmd(stringstream &commandline, string command){

}
void System::putCmd(stringstream &commandline, string command){
    
}


void System::addMajor(Major* m){
    majors.push_back(m);
}
void System::addCourse(Course* c){
    courses.push_back(c);
}
void System::addUser(User * u){
    users.push_back(u);
}