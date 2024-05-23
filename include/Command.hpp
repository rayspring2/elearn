#pragma once
#include "Global.hpp"
enum CmdType{
	GET , PUT , POST , DELETE
};

class Command{
protected:
	CmdType cmd_type;
	
};

class GetCommand: public Command {
	
};