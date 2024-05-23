#pragma once
#include "Global.hpp"

class Subject {
private:
	int id;
	string name;
	int credit;
	int prerequisite;
	vector<int> majors_id;
public:
	Subject(int id, string name, int credit, int prerequisite, vector<int> majors_id );
	string getName();
	void print();
	void shortPrint();
};