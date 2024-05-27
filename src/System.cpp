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

        int major_id = stoi(input[2][0]);
        Major* major = findMajor(major_id);
        Professor* new_professor = new Professor( stoi( input[0][0] ), input[1][0],
        major, input[3][0], input[4][0] );
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
    
    User* user = findUser(id);
    if(!(user->PasswordisEqualTo(password))){
        throw runtime_error(PERMISSIONDENIED); 
    }
    current_user = user;
}

void System::printCourseList(vector<string> &output){
    if(offered_courses.empty())
        throw runtime_error(EMPTYLIST);
    for( OfferedCourse * c : offered_courses ){
        c->shortPrint(output);
    }
}
bool System::userIsStudent(){
    if(dynamic_cast<Student*>(current_user))
        return 1;
    return 0;

}
bool System::userIsProfessor(){
    if(dynamic_cast<Professor*>(current_user))
        return 1;
    return 0;
}
bool System::userIsAdmin(){
    if(dynamic_cast<Admin*>(current_user))
        return 1;
    return 0;
}
void System::printCourse(int id, vector<string> &output){
    OfferedCourse* course =  findOfferedCourse(id);
    course->detailedPrint(output);
} 


void System::addPost( string title, string message){
    current_user->addNewPost(title, message);
}
void System::deletePost(int id){
    current_user->deletePost(id);
}
void System::getPersonalPage(int id, vector<string> &output){
    User* user = findUser(id);
    user->getPersonalPage(output); 
}

User* System::findUser(int id){
    auto it = find_if(users.begin(), users.end(), [id]( User* & u ){
        return u->getId() == id;
    });
    if(it == users.end())
        throw runtime_error(NOTFOUND);
    return *it;
}
void System::viewPost(int user_id, int post_id, vector<string> &output){
    User* user = findUser(user_id);
    cout <<"user info ==" << user->getPrint() << endl;
    Post* post = user->findPost(post_id);
    cout <<"post info == " << post->print() << endl;
    output.push_back(user->getPrint());
    output.push_back(post->print());
}

void System::connect(int id){
    if(!isLoggedIn())
        throw runtime_error(PERMISSIONDENIED);
    User* user = findUser(id);
    current_user->connect(user);
}

void System::viewNotification(vector<string> &output){
    current_user->viewNotifications(output);
}

void System::courseOffer(int course_id, int professor_id,int capacity, Time time, Date exame_date, int class_numebr ){
    Course* course = findCourse(course_id);
    User* user = findUser(professor_id);
    Professor* professor = dynamic_cast<Professor*>(user);

    if(!professor)
        throw runtime_error(PERMISSIONDENIED);


    if(!course->majorHas(professor->getMajorId())){
        throw runtime_error(PERMISSIONDENIED);
    }

    OfferedCourse* new_offered_course = new OfferedCourse(offered_courses.size() + 1, course, professor->getId() ,
    professor->getName(), capacity, time, exame_date, class_numebr);
    if( prevCourseshasConflictWith(new_offered_course)){
        throw runtime_error(PERMISSIONDENIED);
    }
    offered_courses.push_back(new_offered_course);
    professor->addCourse(new_offered_course);
    admin->sendNotification(professor->getId(), professor->getName(), NEW_COURSE_OFFERING_STR);

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

void System::addStudentCourse(int course_id){
    Student* current_student = dynamic_cast<Student*>(current_user);
    OfferedCourse* offered_course = findOfferedCourse(course_id);
    current_student->addCourse(offered_course);     
}

OfferedCourse* System::findOfferedCourse(int course_id){
    for(auto c : offered_courses){
        if(course_id == c->getId()){
            return c;
        }
    }
    throw runtime_error(NOTFOUND);
}

void System::deleteCourse(int id){
    Student* current_student = dynamic_cast<Student*>(current_user);
    current_student->deleteCourse(id);
}

void System::viewMyCourses(vector<string> &output){
    Student* current_student = dynamic_cast<Student*>(current_user);
    current_student->viewCourses(output);
}

