#include "University.hpp"

University::University(char* argv[]){
	system.readData(argv);
    SystemHandler::setSystem(system);
    mapServerPaths(server);
}
void University::mapServerPaths(Server& server) {
    server.setNotFoundErrPage("static/404.html");
    server.get("/", new ShowPage("static/home.html"));
    server.get("/home.png", new ShowImage("static/home.png"));
    
    server.get("/loggedin", new ShowPage("static/loggedin.html"));
    server.get("/login", new ShowPage("static/logincss.html"));
    server.post("/login", new LoginHandler());
    
    server.get("/personal_page", new showPersonalPageHandler());
    server.get("/admin_home", new ShowPage("static/admin_home.html"));
    server.get("/professor_home", new ShowPage("static/professor_home.html"));
    server.get("/student_home", new ShowPage("static/student_home.html"));
    server.get("/student_home/user", new studentGetinfoHandler());
    server.get("/profile_photo", new profileImageHandler());

    server.get("/posts", new showPostsHandler());
    server.get("/addpost", new ShowPage("static/addpost.html"));
    server.post("/post_upload", new postUploadHandler());
    server.get("/post", new showPostbyIdHandler());
    server.get("/student_home/show_offered_course", new ShowPage("static/offered_courses.html"));
    server.get("/student_home/show_offered_course/courses", new showOfferedCoursesHandler());
    
    server.get("/student_home/show_mycourses", new ShowPage("static/student_courses.html"));
    server.get("/student_home/show_mycourses/courses", new showStudentCourseHandler());
    server.get("/student_home/delete_course", new ShowPage("static/delete_course.html"));
    server.post("/student_home/delete_course", new deleteCourseHandler());
    server.get("/student_home/add_course", new ShowPage("static/add_student_course.html"));
    server.post("/student_home/add_course", new addStudentCourseHandler());
    server.get("/addcourse", new ShowPage("static/addcourse.html"));
    server.post("/addcourse", new addCourseHandler());

    server.post("/find_user", new findUserHandler());

    server.get("/up", new ShowPage("static/upload_form.html"));
    server.post("/up", new UploadHandler());
    
    server.post("/logout" , new logoutHandler());
}

void University::run(){
	server.run();
}