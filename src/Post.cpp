#include "Post.hpp"

Post::Post(int id, string title, string message):
 id(id), title(title), message(message){}

string Post::getShortPrint(){
	return to_string(id) + ' ' + '\"' + title + '\"' + '\n';  
}
string Post::print(){
	return to_string(id) + ' ' + "\"" + title + "\"" + ' ' + "\"" + message + "\"" + '\n';
}
int Post::getId(){
	return id;
}