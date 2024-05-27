#include "Course.hpp"

Course::Course(int id, string name, int credit, int prerequisite, vector<int> majors_id )
: id(id), name(name), credit(credit), prerequisite(prerequisite), majors_id(majors_id){
	
}

string Course::getName(){
	return name;
}
int Course::getId(){
	return id;
}

string Course::getShortPrint(){
	return to_string(id) + SPACE + name + NEXTLINE;
}
bool Course::majorHas(int id){
	for(int i : majors_id ){
		if( i == id ){
			return 1;
		}
	}
	return 0;
}
int Course::getPrequisite(){
	return prerequisite;
}