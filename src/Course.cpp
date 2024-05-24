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
void Course::print(){
	cout << "id= " << id << endl;
	cout << "name= " << name <<endl;
	cout << "credit= " << credit <<endl;
	cout << "prerequisties= " << prerequisite << endl;
	cout << "majors_id= " << endl;
	for(auto x : majors_id){
		cout << x << " ";
	}
	cout << endl;
}

void Course::shortPrint(){
	cout << id << ' ' << name << endl;
}
bool Course::majorHas(int id){
	for(int i : majors_id ){
		if( i == id ){
			return 1;
		}
	}
	return 0;
}