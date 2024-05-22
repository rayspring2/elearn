#include <iostream>
#include <sstream>
#include <fstream>
#include <istream>
using namespace std;
int main(){
    ifstream input("professors.csv");
	string x;
	while(getline(input,x)){
		cout << x[x.size()-1] <<endl;
	}
	
}