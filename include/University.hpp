#pragma once
#include "System.hpp"
#include "../server/server.hpp"
#include "Handler.hpp"


class University{
private:
	Server server;
    System system;
public:
	University(char* argv[]);
	void mapServerPaths(Server& server);
	void run();
	
};