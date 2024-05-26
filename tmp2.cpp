/* 
POST login ? id 810102612 password ImtheproblemItsme
POST post ? title "hi" message "aaaaaaaaa"
POST connect ? id 810102342
GET notification ?
POST logout ?
POST login ? id 810102342 password meoow
GET notification ?
GET personal_page ? id 810102342
GET post ? id 810102612 post_id 1

 */
#include "include/Global.hpp"

class Time{
private:
    const vector<string> WEEKDAYS {"sunday", "monday", "tuesday", "wednesday", "thursday", "friday", "saturday"};

public:
    string day;
    int begin_time;
    int end_time;
    Time(string time_str);

};

// Time::Time(string time_str){
//     auto pos = time_str.find(":");
//     if(pos == string::npos){
//         throw runtime_error(BADREQUEST);
//     }

//     day = time_str.substr(0, pos);
//     transform(day.begin(), day.end(), day.begin(), [](char c){return tolower(c);});
//     time_str = time_str.substr(pos+1);
//     if(find(WEEKDAYS.begin(), WEEKDAYS.end(), day) == WEEKDAYS.end()){
//         throw runtime_error(BADREQUEST);
//     }

//     pos = time_str.find("-");
//     if(pos == string::npos){
//         throw runtime_error(BADREQUEST);
//     }

//     begin_time = stoi( time_str.substr(0 , pos));
//     end_time = stoi( time_str.substr( pos+1 ));
// }

int main(){
    ofstream myfile;
    myfile.open("hii.txt");
    myfile << "helooooooo\n";
}


