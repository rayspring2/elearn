#pragma once
#include "Global.hpp"

class Post{
protected:
	int id;
	string title, message;
	string picpath = EMPTYPIC;
public:
	Post(int id, string title, string message, string picpath=EMPTYPIC);
	virtual string getShortPrint();
	virtual string print();
	int getId();
	string getTitle();
	string getMessage();
};