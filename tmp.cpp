#include <iostream>
#include <sstream>
#include <fstream>
#include <istream>
#include <vector>
#include <exception>
#include <stdexcept>
using namespace std;
const string BADREQUEST = "baddddd";

string divString( string &input , char delim, char message_delim){
    string x = "";
    while( !input.empty()){
        if(input[0] == ' ')
            input.erase(input.begin());
        else
            break;
    }
	
	if(!input.empty() && input[0] == message_delim){
		input.erase(input.begin());
		while( !input.empty() && input[0] != message_delim){
			x = x + input[0];
			input.erase(input.begin());
		}
		if(input.empty()){
			throw runtime_error(BADREQUEST);
		}
		input.erase(input.begin());
	}
	else{
		while(!input.empty()) {
			if( input[0] == delim )
				break;
			x = x + input[0];
			input.erase(input.begin());
		}
	}
    if(x.empty()){
		throw runtime_error( BADREQUEST );
    }
	if(input.size() == 0 || input[0] == delim)
    	return x;
	else{
		throw runtime_error(BADREQUEST);
	}
}

string findGetValue( string word , string &str , char delim = ' ' , char message_delim='\"' ){
    str = delim + str + delim;
	word = delim + word + delim;
    size_t pos = str.find(word);
    if(pos == string::npos){
		throw runtime_error(BADREQUEST);
    }
    // bool word_is_seperated = (pos == 0 || !isalnum(str[pos - 1])) &&
    //     (pos + word.length() == str.length() || !isalnum(str[pos + word.length()]));
    // if (!word_is_seperated) {
    //     throw runtime_error(BADREQUEST);
    // }
	cout <<"|" << str[pos] <<"|" << endl;
    string str_r = str.substr(pos + word.length());
    string str_l = str.substr(0 , pos);
    cout <<"str_l =" << str_l << "|" << endl;
	cout <<"str_r =" << str_r << "|"<< endl;
    string value = divString( str_r , delim , message_delim);
	str = str_l + str_r;
    return value;
}




int main(){
    string x;
	while(1){
		getline(cin,x);
		try{
			string ans = findGetValue("id" , x);
			cout << "ans==" << ans<<"|" << endl;
			cout << "x==" << x << endl;
		}
		catch(const runtime_error &ev){
			cout << ev.what();
		}
		cout <<"----------------------------\n";
	}

}