#include "handler.hpp"

System SystemHandler::system = {}; 

void SystemHandler::setSystem(System in_system){
	system = in_system;
}


Response* LoginHandler::callback(Request* req) {
	Response* res;
	try{
		int id = getWholeNumb(req->getBodyParam("username"));
		std::string password = req->getBodyParam("password");
		system.login(id, password);
		res = new Response();
		res->setBody(OK);
		res->setSessionId(to_string(id));
	}
	catch(runtime_error &e){
		res = new Response(Response::Status::badRequest);
		res->setBody("Failed");
	}
	return res;
}

Response* showPersonalPageHandler::callback(Request* req){
	Response* res;
	try{
		if(!system.isLoggedIn())
			throw runtime_error(PERMISSIONDENIED);
		if(system.userIsAdmin()){
			res = Response::redirect("/admin_home");
		}
		else if(system.userIsProfessor()){
			res = Response::redirect("/professor_home");
		}
		else if(system.userIsStudent()){
			res = Response::redirect("/student_home");
		}
	}
	catch(runtime_error &e){
		res= Response::redirect("/login");
	}
	return res;
}


Response* studentGetinfoHandler::callback(Request* req) {
	Response* res;
	try{
		if(!system.isLoggedIn()){
			res = Response::redirect("/login");
			return res;
		}
		int user_id = getWholeNumb(req->getSessionId());
		res = new Response();
		int id = system.getUserid(user_id);
		string name = system.getUserName(user_id);
		string major = system.getUserMajor(user_id);
		string body = "{  \"id\": \"" + to_string(id) 
				 + "\", \"name\": \"" + name 
				 + "\", \"major\": \"" + major + "\" }\n";
		
		res->setBody(body);
	}
	catch(runtime_error &e){
		res = new Response(Response::Status::unauthorized);
		res->setBody(e.what());
	}	
	return res;
}


Response* UploadHandler::callback(Request* req) {
	if(!system.isLoggedIn()){
			Response* res = Response::redirect("/login");
			return res;
	}
    string name = "pic/" + req->getSessionId()+".png";
    string file = req->getBodyParam("file");
	system.setUserProfilePhoto(name);
    utils::writeToFile(file, name);
    Response* res = Response::redirect("/personal_page");
    return res;
}

Response* profileImageHandler::callback(Request* req){
	if(!system.isLoggedIn()){
			Response* res = Response::redirect("/login");
			return res;
	}
	int user_id = getWholeNumb(req->getSessionId());
	string profilephoto_url = system.getUserProfilePhotoUrl(user_id);

    ShowFile file(profilephoto_url, "image/png");
	return file.callback(req);
    
}

Response* showPostsHandler::callback(Request* req){
	if(!system.isLoggedIn()){
		Response* res = Response::redirect("/login");
		return res;
	}
	
	int user_id;
	if(req->getQueryParam("user_id").empty())
		user_id = getWholeNumb(req->getSessionId());
	else
		user_id = getWholeNumb(req->getQueryParam("user_id"));
	
	vector<Post*> posts = system.getUserPosts(user_id);
	string body = "";
	for(auto p : posts){
		body +=  "<div class='post'>";
        body += "<div class='post-title'>"+ p->getTitle() +"</div>";
		body += "<div class='post-message'>" + p->getMessage() + "</div>";
		if(p->hasImage()){
            body += "<img src=\"/post?post_id="
			+ to_string(p->getId()) + "&user_id="+ to_string(user_id) + "\" alt='Post Image'>";
		}
		body += "</div>";
	}
	Response* res = new Response();

	res->setBody(body);
	return res;
}

Response* postUploadHandler::callback(Request* req){
	if(!system.isLoggedIn()){
			Response* res = Response::redirect("/login");
			return res;
	}

	string name = "pic/" + req->getSessionId()+ "_post_" + to_string(system.getUserNextPostId()) +".png";
    string file = req->getBodyParam("file");
	string title = req->getBodyParam("title");
	string message = req->getBodyParam("message");
	system.addPost(title, message, name);
    utils::writeToFile(file, name);
    Response* res = Response::redirect("/personal_page");
    return res;
}

Response* showPostbyIdHandler::callback(Request* req){	
	if(!system.isLoggedIn()){
			Response* res = Response::redirect("/login");
			return res;
	}
	int user_id =  getWholeNumb(req->getQueryParam("user_id"));
	int post_id = getNatrualNumb(req->getQueryParam("post_id"));
	Post* post = system.findUserPost(user_id, post_id);
	ShowFile file(post->getPicPath(), "image/png");
	return file.callback(req);
}

Response* showOfferedCoursesHandler::callback(Request* req){	
	Response* res = new Response();
	res->setBody(system.printCourseList());
	return res;
}


Response* addCourseHandler::callback(Request* req){	
	if(!system.userIsAdmin()){
			Response* res = Response::redirect("/login");
			return res;
	}
	Response* res;
	try{
		res = new Response();
		int course_id = getNatrualNumb(req->getBodyParam("course_id"));
		int professor_id = getNatrualNumb(req->getBodyParam("professor_id"));
		int capacity = getNatrualNumb(req->getBodyParam("capacity"));
		Time time(req->getBodyParam("time"));
		string exame_date = req->getBodyParam("exame_date");
		int class_numb = getNatrualNumb(req->getBodyParam("class_number"));
		res->setBody(OK);
		system.courseOffer(course_id, professor_id, capacity , time, exame_date, class_numb );
	}
	catch(runtime_error &e){
		res = new Response(Response::Status::badRequest);
		res->setBody(e.what());
	}
	return res;
}

Response* logoutHandler::callback(Request* req){	
	Response* res = new Response();
	system.logout();
	res->setSessionId("");
	res = Response::redirect("/login");
	return res;
}

Response* showStudentCourseHandler::callback(Request* req){	
	try{
		if(!system.userIsStudent()){
			Response* res = Response::redirect("/login");
			return res;
		}
		Response* res = new Response();
		res->setBody(system.viewMyCourses());
		return res;
	}
	catch(runtime_error &e){
		Response* res = Response::redirect("/personal_page");
		return res;
	}
}

Response* deleteCourseHandler::callback(Request* req){
	if(!system.isLoggedIn()){
		Response* res = Response::redirect("/login");
		return res;
	}
	Response* res; 	
	try{
		res = new Response();
		int course_id = getNatrualNumb(req->getBodyParam("course_id"));
		system.deleteCourse(course_id);
	}
	catch(runtime_error &e){
		res = new Response(Response::Status::badRequest);
	}
	return res;
}

Response* addStudentCourseHandler::callback(Request* req){
	if(!system.isLoggedIn()){
		Response* res = Response::redirect("/login");
		return res;
	}
	Response* res; 	
	try{
		res = new Response();
		int course_id = getNatrualNumb(req->getBodyParam("course_id"));
		system.addStudentCourse(course_id);
	}
	catch(runtime_error &e){
		res = new Response(Response::Status::badRequest);
		res->setBody(e.what());
	}
	return res;
}

Response* findUserHandler::callback(Request* req){
	if(!system.isLoggedIn()){
		Response* res = Response::redirect("/login");
		return res;
	}
	Response* res;
	try{
		res = new Response();
		int userid = getWholeNumb(req->getBodyParam("userId"));
		if(system.userIsAdmin(userid))
			res = Response::redirect("/admin_view_page?userid=" + to_string(userid));
		if(system.userIsProfessor(userid))
			res = Response::redirect("/professor_view_page?userid=" + to_string(userid));
		if(system.userIsStudent(userid))
			res = Response::redirect("/student_view_page?userid=" + to_string(userid));
	}
	catch(runtime_error &e){
		res = new Response(Response::Status::badRequest);
		res->setBody(e.what());
	}
	return res;
}


Response* getStudentPageInfoHandler::callback(Request* req){
	Response* res;
	try{
		res = new Response();
		int user_id = getNatrualNumb(req->getQueryParam("user_id"));
		
		int id = user_id;
		string name = system.getUserName(user_id);
		string major = system.getUserMajor(user_id);
		int semester = system.getStudentSemester(user_id);
		string body = "{  \"id\": \"" + to_string(id) 
				 + "\", \"name\": \"" + name 
				 + "\", \"semester\": \"" + to_string(semester)
				 + "\", \"major\": \"" + major + "\" }\n";
		
		res->setBody(body);
	}
	catch(runtime_error &e){
		res = new Response(Response::Status::badRequest);
		res->setBody(e.what());
	}
	return res;
}


Response* getProfessorPageInfoHandler::callback(Request* req){
	Response* res;
	try{
		res = new Response();
		int user_id = getNatrualNumb(req->getQueryParam("user_id"));
		
		int id = user_id;
		string name = system.getUserName(user_id);
		string major = system.getUserMajor(user_id);
		string posisition = system.getProfessorPos(user_id);
		string body = "{  \"id\": \"" + to_string(id) 
				 + "\", \"name\": \"" + name 
				 + "\", \"position\": \"" + posisition
				 + "\", \"major\": \"" + major + "\" }\n";
		
		res->setBody(body);
	}
	catch(runtime_error &e){
		res = new Response(Response::Status::badRequest);
		res->setBody(e.what());
	}
	return res;
}

Response* getAdminPageInfoHandler::callback(Request* req){
	Response* res;
	try{
		res = new Response();
		int user_id = getWholeNumb(req->getQueryParam("user_id"));
		
		int id = user_id;
		string name = system.getUserName(user_id);
		string body = "{  \"id\": \"" + to_string(id) 
				 + "\", \"name\": \"" + name  + "\" }\n";
		res->setBody(body);
	}
	catch(runtime_error &e){
		res = new Response(Response::Status::badRequest);
		res->setBody(e.what());
	}
	return res;
}


