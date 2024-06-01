#include "TAFormPost.hpp"

const string TAFormPost::TA_FORM_FOR_STR = "TA form for ";
const string TAFormPost::COURSE_STR = "course";

TAFormPost::TAFormPost(string course_info, string course_name, int post_id, string message, int min_semester):
course_info(course_info), min_semester(min_semester), 
Post(post_id, TA_FORM_FOR_STR + SPACE + course_name + SPACE + COURSE_STR , message){
}

string TAFormPost::print(){
	string outstr = getShortPrint();
	outstr += course_info + NEXTLINE;
	outstr += message + NEXTLINE;
	return outstr;
}

void TAFormPost::addApplicant(int id, string name, int semester){
	if(semester <= min_semester)
		throw runtime_error(PERMISSIONDENIED);
	StudentInfo new_applicant(id, name, semester);
	applicants.push_back(new_applicant);
}


