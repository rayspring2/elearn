#pragma once
#include "Global.hpp"

class Post{
private:
	int id;
	string title, message;
public:
	Post(int id, string title, string message);
	string getShortPrint();
	string print();
	int getId();
};