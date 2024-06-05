#include "TAFormPost.hpp"

const string TAFormPost::CLOSE_FORM_BEGIN_STR = "We have received ";
const string TAFormPost::CLOSE_FORM_END_STR = " requests for the teaching "
"assistant position";
	
const string TAFormPost::TA_FORM_FOR_STR = "TA form for";
const string TAFormPost::COURSE_STR = "course";

Applicant::Applicant(int id, string name, int semester): 
id(id), name(name), semester(semester){}

string Applicant::getPrint(){
	return NEXTLINE + to_string(id) + SPACE + name + SPACE + to_string(semester) + COLON + SPACE;
}

TAFormPost::TAFormPost(string course_info, string course_name, int course_id, int post_id, string message, int min_semester):
course_info(course_info), min_semester(min_semester), course_id(course_id),
Post(post_id, TA_FORM_FOR_STR + SPACE + course_name + SPACE + COURSE_STR , message){
}

string TAFormPost::print(){
	string outstr = getShortPrint();
	outstr += course_info;
	outstr += QUATATION + message + QUATATION + NEXTLINE;
	return outstr;
}

void TAFormPost::addApplicant(int id, string name, int semester){
	if(semester <= min_semester)
		throw runtime_error(PERMISSIONDENIED);
	Applicant new_applicant(id, name, semester);
	applicants.push_back(new_applicant);
}

vector<string> TAFormPost::getApplicantsPrints(vector<string> &output){
	vector<string> applicantsprint;
	int applicants_cnt = applicants.size();
	output.push_back(CLOSE_FORM_BEGIN_STR + 
	to_string(applicants_cnt) + CLOSE_FORM_END_STR);
	for( Applicant p : applicants )
		applicantsprint.push_back(p.getPrint());
	
	return applicantsprint;
}

vector<int> TAFormPost::getApplicantids(){
	vector<int> output;
	for(Applicant p : applicants){
		output.push_back(p.id);
	}
	return output;
}

int TAFormPost::getCourseId(){
	return course_id;
}

string TAFormPost::getShortPrint(){
	return to_string(id) + SPACE + title + NEXTLINE;  
}



