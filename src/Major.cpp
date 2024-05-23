#include "Major.hpp"

Major::Major(int id, string name) : id(id), name(name){}

int Major::getId(){
	return id;
}
string Major::getName(){
	return name;
}
void Major::print(){
	cout <<"id= " << id <<endl;
	cout << "name=" << name << endl;
}