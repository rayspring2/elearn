#include "Course.hpp"

Course::Course(int cid, string name, int credit, int prerequisite, vector<int> majors_id )
: cid(cid), name(name), credit(credit), prerequisite(prerequisite), majors_id(majors_id){
	
}

void Course::print(){
	cout << "cid= " << cid << endl;
	cout << "name= " << name <<endl;
	cout << "credit= " << credit <<endl;
	cout << "prerequisties= " << prerequisite << endl;
	cout << "majors_id= " << endl;
	for(auto x : majors_id){
		cout << x << " ";
	}
	cout << endl;
}