#include "System.hpp"
const string System::NEW_COURSE_OFFERING_STR = "New Course Offering";
System::System(){
    addUser(admin);
}

void System::readData( char* argv[]){
	ifstream majors_file(MAJORSPATH);
    ifstream course_file(COURSESPATH);
    ifstream professors_file(PROFESSORPATH);
    ifstream students_file(STUDENTPATH);
	ofstream ouput("output.txt");
    readMajorData(majors_file);
    readCourseData(course_file);
    readProfessorData(professors_file);
    readStudentData(students_file);

    for(User* u : users){
        User* admin = users[0];
        admin->connect(u);
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

void System::courseOffer(int course_id, int professor_id,int capacity, Time time, Date exame_date, int class_numebr ){
    if(current_user != admin)
        throw runtime_error(PERMISSIONDENIED);
    
    Course* course = findCourse(course_id);
    User* user = findUser(professor_id);
    Professor* professor = dynamic_cast<Professor*>(user);

    if(!professor)
        throw runtime_error(PERMISSIONDENIED);
    OfferedCourse* new_offered_course = new OfferedCourse(course, professor, capacity, time, exame_date, class_numebr);
    if( prevCourseshasConflictWith(new_offered_course)){
        throw runtime_error(PERMISSIONDENIED);
    }
    offered_courses.push_back(new_offered_course);
    professor->sendNotification(NEW_COURSE_OFFERING_STR);
}

bool System::prevCourseshasConflictWith(OfferedCourse* new_course){
    for(OfferedCourse* oc : offered_courses){
        if(oc->getProfessorId() != new_course->getProfessorId())
            continue;
        if(oc->hasTimeConflict(new_course))
            return 1;
    }
    return 0;
}

Course* System::findCourse(int id){
    auto it = find_if(courses.begin(), courses.end(), [id](Course* & c){
        return c->getId() == id;
    });

    if(it == courses.end())
        throw runtime_error(NOTFOUND);
    
    return *it;
}

