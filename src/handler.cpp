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
		res->setBody("Successful");
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
		string body = "{ \"profilephoto\":\"" + profilephoto_url + "\" , \"id\": \"" + to_string(id) + "\", \"name\": \"" +name + "\", \"major\": \"" + major + "\" }\n";
		ofstream file("1.txt");
		file << body << endl;
		res->setBody(body);
	}
	catch(runtime_error &e){
		res = new Response(Response::Status::badRequest);
		res->setBody("Please login first");
	}	
	return res;
}



