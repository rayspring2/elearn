#pragma once
#include "Global.hpp"

class Course {
private:
	int id;
	string name;
	int credit;
	int prerequisite;
	vector<int> majors_id;
public:
	Course(int id, string name, int credit, int prerequisite, vector<int> majors_id );
	void print();
	void shortPrint();
};