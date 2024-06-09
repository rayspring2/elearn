#include "handler.hpp"

System SystemHandler::system = {}; 

void SystemHandler::setSystem(System in_system){
	system = in_system;
}


Response* LoginHandler::callback(Request* req) {
    std::string username = req->getBodyParam("username");
    std::string password = req->getBodyParam("password");
    if (username == "root") {
        throw Server::Exception("Remote root access has been disabled.");
    }
    std::cout << "username: " << username << ",\tpassword: " << password << std::endl;
    Response* res = Response::redirect("/rand");
    res->setSessionId("SID");
    return res;
}