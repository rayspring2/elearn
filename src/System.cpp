#include "System.hpp"
const string System::NEW_COURSE_OFFERING_STR = "New Course Offering";
const string System::TA_REQUEST_NOTIF_STR = "Your request to be a teaching assistant has been ";
const string System::ACCEPTED_STR = "accepted.";
const string System::REJECTED_STR = "rejected.";
const string System::NEW_COURSE_POST_STR = "New Course Post";
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
    
    while(getline(professor_file , line)) {
        int id = getNatrualNumb(divString(line, COMMA));
        string name = divString(line, COMMA);
        int major_id = getNatrualNumb(divString(line, COMMA));
        Major* major = findMajor(major_id);
        string position = divString(line, COMMA);
        string password =  divString(line, COMMA);
        
        Professor* new_professor = new Professor( id, name, major, position, password );
        addUser(new_professor);
    }
}


void System::readStudentData(ifstream &student_file){
    string line;
    getline( student_file, line );
    
    while(getline(student_file , line)) {
        int id = getNatrualNumb(divString(line, COMMA));
        string name = divString(line, COMMA);
        int major_id = getNatrualNumb(divString(line, COMMA));
        Major* major = findMajor(major_id);
        int semester = getNatrualNumb(divString(line, COMMA));
        string password =  divString(line, COMMA);

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
        output.push_back(c->getShortPrint());
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


bool System::isStudent(User* user){
    if(dynamic_cast<Student*>(user))
        return 1;
    return 0;

}
bool System::isProfessor(User* user){
    if(dynamic_cast<Professor*>(user))
        return 1;
    return 0;
}
bool System::isAdmin(User* user){
    if(dynamic_cast<Admin*>(user))
        return 1;
    return 0;
}
bool System::isTaForm(Post* post){
    if(dynamic_cast<TAFormPost*>(post))
        return 1;
    return 0;
}


void System::printCourse(int id, vector<string> &output){
    OfferedCourse* course =  findOfferedCourse(id);
    output.push_back(course->getDetailedPrint());
} 


void System::addPost( string title, string message, string image_path){
    current_user->addNewPost(title, message, image_path);
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
    Post* post = user->findPost(post_id);
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


    if(!course->majorHas(professor->getMajorId()))
        throw runtime_error(PERMISSIONDENIED);
    

    OfferedCourse* new_offered_course = new OfferedCourse(offered_courses.size() + 1, course, professor->getId() ,
    professor->getName(), capacity, time, exame_date, class_numebr);
    if( prevCourseshasConflictWith(new_offered_course))
        throw runtime_error(PERMISSIONDENIED);
    
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
    offered_course->addStudent(current_student->getId());     
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
    OfferedCourse* course = findOfferedCourse(id);
    current_student->deleteCourse(id);
    course->deleteParticipant(current_student->getId());
    
}

void System::viewMyCourses(vector<string> &output){
    Student* current_student = dynamic_cast<Student*>(current_user);
    current_student->viewCourses(output);
}


void System::setProfilePhoto(string profile_photo_path){
    current_user->setProfilePhoto(profile_photo_path);
}

void System::addCoursePost(int offered_course_id, string title, 
string message, string image_path){
    OfferedCourse* course = findOfferedCourse(offered_course_id);
    
    course->addPost(current_user->getId(), title, message, image_path);
    vector<int> participant_ids = course->getParticipantIds();
    for(int i : participant_ids){
        if( i == current_user->getId())
            continue;
        User* user = findUser(i);
        user->addNotification(course->createNotification(NEW_COURSE_POST_STR));
    }
}

void System::viewCourseChannel(int course_id, vector<string> &output){
    OfferedCourse* course = findOfferedCourse(course_id);
    if(!course->isAParticipant(current_user->getId()))
        throw runtime_error(PERMISSIONDENIED);
    output.push_back(course->getChannelPrint(users));
}
void System::ViewCourseChannelPost(int course_id, int post_id, vector<string> &output){
    OfferedCourse* course = findOfferedCourse(course_id);
    if(!course->isAParticipant(current_user->getId()))
        throw runtime_error(PERMISSIONDENIED);
    output.push_back(course->getChannelPostPrint(post_id, users));

}

void System::addTAForm(int course_id, string message){
    OfferedCourse* course = findOfferedCourse(course_id);
    if(!course->isAParticipant(current_user->getId()))
        throw runtime_error(PERMISSIONDENIED);
    Professor* professor = dynamic_cast<Professor*>(current_user);
    professor->addTAForm(course, message);    
}

vector<string> System::getApplicantsPrint(int form_id, vector<string> &output){
    Professor* professor = dynamic_cast<Professor*>(current_user);
    TAFormPost* ta_form = professor->findTaForm(form_id);
    return ta_form->getApplicantsPrints(output);
}

void System::applyAcceptedTa(vector<bool> applicants_acceptance_status, int form_id){
    Professor* professor = dynamic_cast<Professor*>(current_user);
    TAFormPost* ta_form = professor->findTaForm(form_id);
    OfferedCourse* offered_course = findOfferedCourse(ta_form->getCourseId());
    vector<int> ta_applicant_ids = ta_form->getApplicantids();
    for(int i = 0; i < ta_applicant_ids.size(); i++){
        string message = TA_REQUEST_NOTIF_STR;
        if(applicants_acceptance_status[i]){
            offered_course->addTA(ta_applicant_ids[i]);
            message += ACCEPTED_STR;
        }
        else{
            message += REJECTED_STR;
        }
        User* user = findUser(ta_applicant_ids[i]);
        user->addNotification(offered_course->createNotification(message));
    } 
    deletePost(form_id);
}

void System::addTaRequest(int professor_id, int form_id){
    Student* student = dynamic_cast<Student*>(current_user);
    User* user = findUser(professor_id);
    if(!isProfessor(user))
        throw runtime_error(NOTFOUND);
    Professor* professor = dynamic_cast<Professor*>(user);
    
    TAFormPost* ta_form = professor->findTaForm(form_id);
    
    ta_form->addApplicant(student->getId(), student->getName(), student->getSemester());
}

int System::getUserid(){
    return current_user->getId();
}

string System::getUserName(){
    return current_user->getName();
}

string System::getUserMajor(){
    if(isAdmin(current_user) or !isLoggedIn())
        throw runtime_error(BADREQUEST);
    if(isStudent(current_user)){
        Student* st = dynamic_cast<Student*>(current_user);
        return st->getMajorName();
    }
    else{
        Professor* prof = dynamic_cast<Professor*>(current_user);
        return prof->getMajorName();
    }
}


