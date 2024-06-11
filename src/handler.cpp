#include "handler.hpp"

System SystemHandler::system = {}; 

void SystemHandler::setSystem(System in_system){
	system = in_system;
}


Response* LoginHandler::callback(Request* req) {
	Response* res = new Response();
	try{
		int id = getWholeNumb(req->getBodyParam("username"));
		std::string password = req->getBodyParam("password");
		system.login(id, password);
		
		res->setBody("Successful");
		res->setSessionId(to_string(id));
	}
	catch(runtime_error &e){
		res = new Response(Response::Status::badRequest);
		res->setBody("Failed");
	}
	return res;
}

Response* addPostHandler::callback(Request* req) {
	
}



