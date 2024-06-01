#include "Post.hpp"

Post::Post(int id, string title, string message, string picpath = EMPTYPIC):
 id(id), title(title), message(message), picpath(picpath) {}

string Post::getShortPrint(){
	return to_string(id) + SPACE + QUATATION + title + QUATATION + NEXTLINE;  
}
string Post::print(){
	return to_string(id) + SPACE + QUATATION + title + QUATATION + SPACE + QUATATION + message + QUATATION + NEXTLINE;
}
int Post::getId(){
	return id;
}

string Post::getTitle(){
	return title;
}
string Post::getMessage(){
	return message;
}