#include "System.hpp"

void System::run(){
	
}

void System::readData( char* argv[]){
	ifstream majors_file(MAJORSPATH);
    ifstream courses_file(COURSESPATH);
    ifstream professors_file(PROFESSORPATH);
    ifstream students_file(STUDENTPATH);
	ofstream ouput("output.txt");
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

void System::logout(string &commandline){
    if( !commandline.empty() ){
        throw runtime_error(BADREQUEST);
    }
    if(!isLoggedIn()){
        throw runtime_error(PERMISSIONDENIED);
    }
    current_user = NOT_LOGIN;
}

bool System::isLoggedIn(){
    return !(current_user == nullptr);
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

void System::login(int id, string password){
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
    if(!(user->PasswordisEqualTo(password))){
        throw runtime_error(PERMISSIONDENIED); 
    }
    current_user = user;
}

void System::printCourseList(){
    for( Course * c : courses ){
        c->shortPrint();
    }
}

void System::addPost( string title, string message){
    if(!isLoggedIn())
        throw runtime_error(PERMISSIONDENIED);
    current_user->addNewPost(title, message);
}