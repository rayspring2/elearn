#pragma once
#include "Global.hpp"

class Course {
private:
	int cid;
	string name;
	int credit;
	int prerequisite;
	vector<int> majors_id;
public:
	Course(int cid, string name, int credit, int prerequisite, vector<int> majors_id );
	void print();
};