#include "System.hpp"

System::System(){
    User* admin = new Admin();
    addUser(admin);
}

void System::readData( char* argv[]){
	ifstream majors_file(MAJORSPATH);
    ifstream subject_file(SUBJECTSPATH);
    ifstream professors_file(PROFESSORPATH);
    ifstream students_file(STUDENTPATH);
	ofstream ouput("output.txt");
    readMajorData(majors_file);
    readSubjectData(subject_file);
    readProfessorData(professors_file);
    readStudentData(students_file);

    for(User* u : users){
        cerr << u->getName() << endl;
    }
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


void System::readSubjectData(ifstream &subject_file){
    string line;
    getline( subject_file, line );
    vector<vector<string>> input;
    
    while(getline(subject_file , line)) {
        input = readCSVLine( line );
        vector<int> majors_id;
        
        transform(input[4].begin(), input[4].end(), back_inserter(majors_id),
               [](const string& str) { return stoi(str); });
               
        Subject* new_subject = new Subject( stoi( input[0][0] ) , input[1][0],
        stoi(input[2][0]), stoi(input[3][0]), majors_id);
        addSubject(new_subject);
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
        int id = stoi( input[0][0] );
        string name = input[1][0];
        int major_id = stoi(input[2][0]);
        Major* major = findMajor(major_id);
        int semester = stoi(input[3][0]);
        string password = input[4][0];

        Student* new_student = new Student(id, name, major, semester, password );
        addUser(new_student);
    }
}
Major* System::findMajor(int id){
    auto it = find_if(majors.begin(), majors.end(), [id](Major* &m ){
        return m->getId() == id;
    });

    return *it;
}
void System::logout(){
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
void System::addSubject(Subject* c){
    subjects.push_back(c);
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
    for( Subject * c : subjects ){
        c->shortPrint();
    }
}

void System::addPost( string title, string message){
    if(!isLoggedIn())
        throw runtime_error(PERMISSIONDENIED);
    current_user->addNewPost(title, message);
}
void System::deletePost(int id){
    if(!isLoggedIn())
        throw runtime_error(PERMISSIONDENIED);

    current_user->deletePost(id);
}
void System::getPersonalPage(int id){
    User* user = findUser(id);
    user->getPersonalPage(); 
}

User* System::findUser(int id){
    auto it = find_if(users.begin(), users.end(), [id]( User* & u ){
        return u->getId() == id;
    });
    if(it == users.end())
        throw runtime_error(NOTFOUND);
    return *it;
}
void System::viewPost(int user_id, int post_id){
    User* user = findUser(user_id);
    user->print();
    user->printPost(post_id);
}

void System::connect(int id){
    if(!isLoggedIn())
        throw runtime_error(PERMISSIONDENIED);
    User* user = findUser(id);
    current_user->connect(user);
}

void System::viewNotification(){
    if(!isLoggedIn())
        throw runtime_error(PERMISSIONDENIED);
    current_user->viewNotifications();
}

