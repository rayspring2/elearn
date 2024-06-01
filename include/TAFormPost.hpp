#include "Global.hpp"
#include "Post.hpp"

struct StudentInfo{
	int id,semester;
	string name;
	StudentInfo(int id, string name, int semester): id(id), name(name), semester(semester){}		
};

class TAFormPost : public Post{
private:
	static const string TA_FORM_FOR_STR;
	static const string COURSE_STR;
	string course_info;
	vector<StudentInfo> applicants;
	int min_semester;
public:
	TAFormPost(string course_info,
	string course_name, int post_id, string message, int min_semester);
	string print();
	void addApplicant(int id, string name, int semester);
};