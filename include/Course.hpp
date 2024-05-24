#pragma once
#include "Global.hpp"

class Course {
protected:
	int id;
	string name;
	int credit;
	int prerequisite;
	vector<int> majors_id;
public:
	Course(int id, string name, int credit, int prerequisite, vector<int> majors_id );
	string getName();
	int getId();
	void print();
	void shortPrint();
	bool majorHas(int id);
};