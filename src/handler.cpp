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
	try{
		ofstream file("output.txt");
		file << "11111111111" << endl;
		Response* res = new Response();
		int id = system.getUserid();
		file << id<< endl;
		string name = system.getUserName();
		file << name << endl;
		string major = system.getUserMajor();
		file << major << endl;
		string body = "{ \"id\": \"" + to_string(id) + "\", \"name\": \"" +name + "\", \"major\": \"" + major + "\" }\n";
		//             "{ \"code\": \"500\", \"message\": \"" + msg + "\" }\n"
		res->setBody("{ \"id\": \"500\", \"name\": \" heyname\", \"major\" : \"CE\" }\n");
		//file << "{ \"code\": \"500\", \"message\": \"" + "msg" + "\" }\n" << endl ;
		file << body << endl;
		file <<"2222" << endl;
	}
	catch(runtime_error &e){
		Response* res = new Response(Response::Status::badRequest);
		res->setBody("Please login first");
	}	
}



