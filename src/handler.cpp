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
		
	}
	return res;
}

Response* addPostHandler::callback(Request* req) {
	Response* res;
	try{
		// int 
	}
	catch(runtime_error &e){
		
	}

}

Response* studentGetinfoHandler::callback(Request* req) {
	Response* res;
	try{
		int user_id = getWholeNumb(req->getSessionId());
		res = new Response();
		int id = system.getUserid();
		string name = system.getUserName();
		string major = system.getUserMajor();
		string profilephoto_url = system.getUserProfilePhotoUrl(user_id);
		string body = "{  \"id\": \"" + to_string(id) 
				 + "\", \"name\": \"" + name 
				 + "\", \"major\": \"" + major + "\" }\n";
		
		res->setBody(body);
	}
	catch(runtime_error &e){
		res = new Response(Response::Status::badRequest);
		res->setBody("Please login first");
	}	
	return res;
}


Response* UploadHandler::callback(Request* req) {
    string name = "pic/" + req->getSessionId()+".png";
    string file = req->getBodyParam("file");
	system.setUserProfilePhoto(name);
    utils::writeToFile(file, name);
    Response* res = Response::redirect("/personal_page");
    return res;
}

Response* profileImageHandler::callback(Request* req){
	int user_id = getWholeNumb(req->getSessionId());
	string profilephoto_url = system.getUserProfilePhotoUrl(user_id);

    ShowFile file(profilephoto_url, "image/png");
	return file.callback(req);
    
}

Response* showPostsHandler::callback(Request* req){
	vector<Post*> posts = system.getUserPosts();
	string body = "";
	for(auto p : posts){
		body +=  "<div class='post'>";
        body += "<div class='post-title'>"+ p->getTitle() +"</div>";
		body += "<div class='post-message'>" + p->getMessage() + "</div>";
		if(p->hasImage()){
            body += "<img src=\"/post?post-id="
			+ to_string(p->getId()) + "\" alt='Post Image'>";
		}
		body += "</div>";
	}
	Response* res = new Response();

	res->setBody(body);
	return res;
}

Response* postUploadHandler::callback(Request* req){
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
	int post_id = getNatrualNumb(req->getQueryParam("post-id"));
	Post* post = system.findUserPost(post_id);
	ShowFile file(post->getPicPath(), "image/png");
	return file.callback(req);
}

Response* showOfferedCoursesHandler::callback(Request* req){	
	Response* res = new Response();
	res->setBody(system.printCourseList());
	return res;
}


Response* addCourseHandler::callback(Request* req){	
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
		res->setBody(BADREQUEST);
	}
	return res;
}




