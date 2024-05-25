#include "Post.hpp"

Post::Post(int id, string title, string message):
 id(id), title(title), message(message){}

void Post::shortPrint(){
	cout << id << ' ' << title << endl;  
}
void Post::print(){
	cout <<id << ' ' << "\"" << title << "\"" << ' ' << "\"" << message << "\""<< endl;
}
int Post::getId(){
	return id;
}