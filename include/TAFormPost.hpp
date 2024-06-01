#include "Global.hpp"
#include "Post.hpp"
class TAFormPost : public Post{
private:
	static const string TA_FORM_FOR_STR;
	static const string COURSE_STR;

	string course_info;
public:
	TAFormPost(string course_info,
	string course_name, int post_id, string message);
	string print();
};