#include "Global.hpp"
#include "Post.hpp"

struct Applicant{
	int id,semester;
	string name;
	Applicant(int id, string name, int semester);		
	string getPrint();

};

class TAFormPost : public Post{
private:
	static const string CLOSE_FORM_BEGIN_STR;
	static const string CLOSE_FORM_END_STR;
	static const string TA_FORM_FOR_STR;
	static const string COURSE_STR;
	string course_info;
	vector<Applicant> applicants;
	int min_semester;
	int course_id;
public:
	TAFormPost(string course_info,
	string course_name, int course_id, int post_id, string message, int min_semester);
	string print();
	void addApplicant(int id, string name, int semester);
	vector<string> getApplicantsPrints(vector<string> &ouput);
	vector<int> getApplicantids();
	int getCourseId();
	string getShortPrint();

};