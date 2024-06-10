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
		res = Response::redirect("/loggedin");
		
		res->setSessionId(to_string(id));
	}
	catch(runtime_error &e){
		// cout << e.what() << endl;
		// res->setBody()
	}
	return res;
}