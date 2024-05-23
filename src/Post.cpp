#include "Post.hpp"

Post::Post(int id, string title, string message):
 id(id), title(title), message(message){}
int Post::getId(){
	return id;
}