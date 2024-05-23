#include "Subject.hpp"

Subject::Subject(int id, string name, int credit, int prerequisite, vector<int> majors_id )
: id(id), name(name), credit(credit), prerequisite(prerequisite), majors_id(majors_id){
	
}

string Subject::getName(){
	return name;
}

void Subject::print(){
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

void Subject::shortPrint(){
	cout << id << ' ' << name << endl;
}