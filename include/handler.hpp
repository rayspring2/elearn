#pragma once
#include "Global.hpp"
#include "System.hpp"
#include "../server/server.hpp"

class SystemHandler: public RequestHandler{
protected:
	static System system;
public:
	static void setSystem(System system);
	
};

class LoginHandler : public SystemHandler {
public:
    Response* callback(Request*) override;
};

class showPersonalPageHandler : public SystemHandler{
public:
    Response* callback(Request*) override;
};
class addPostHandler : public SystemHandler {
public:
    Response* callback(Request*) override;
};



