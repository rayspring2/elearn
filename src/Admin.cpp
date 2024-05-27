#include "Admin.hpp"
const int Admin::ADMIN_DEFAULT_ID = 0;
const string Admin::ADMIN_DEFAULT_PASSWORD = "UT_account";
const string Admin::ADMIN_DEFAULT_NAME = "UT_account";
Admin::Admin(int id, string name, string password): User(id, name, password){
    
}
void Admin::getPersonalPage(vector<string> &output){
    output.push_back(getPrint());
    printAllPosts(output);
}
string Admin::getPrint(){
    return name + NEXTLINE;
}
