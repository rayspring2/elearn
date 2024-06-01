#include "TAFormPost.hpp"

const string TAFormPost::TA_FORM_FOR_STR = "TA form for ";
const string TAFormPost::COURSE_STR = "course";

TAFormPost::TAFormPost(string course_info, string course_name, int post_id, string message):
course_info(course_info), 
Post(post_id, TA_FORM_FOR_STR + SPACE + course_name + SPACE + COURSE_STR , message){
}

string TAFormPost::print(){
	string outstr = getShortPrint();
	outstr += course_info;
	outstr += message;
	return outstr;
}


