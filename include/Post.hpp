#pragma once
#include "Global.hpp"

class Post{
private:
	int id;
	string title, message;
	string picpath = EMPTYPIC;
public:
	Post(int id, string title, string message, string picpath);
	string getShortPrint();
	string print();
	int getId();
};