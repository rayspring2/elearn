#include "Global.hpp"

vector<vector<string>> readCSVLine( string line ){
    vector<vector<string>> input;
    vector<string> sametype;
    string s = "";
    while( !line.empty() ){
        char x = line[0];
        line.erase(line.begin());
        if( x != ';' && x != ',' && x != '\n' ){
            s = s + x;
			continue;
        }   
        if( x == ';' || x == ',' || x == '\n'){
            sametype.push_back(s);
            //
            s = "";
        }
		
        if( x == ',' || x == '\n' ){
            input.push_back(sametype);
            sametype.clear();
        }
    }
	sametype.push_back(s);
	input.push_back(sametype);
    return input;
}


string divString( string &input , char delim, char message_delim){
    string x = "";
    input = input + ' ';
    while( !input.empty()){
        if(input[0] == ' ')
            input.erase(input.begin());
        else
            break;
    }
	char search_char = delim;
    if(input[0] == message_delim){
        input.erase(input.begin());
        search_char = message_delim;
    }
    size_t pos = input.find(search_char);
    if( pos == string::npos)
        throw runtime_error(BADREQUEST);
    
    x = input.substr(0, pos);
    input = input.substr(pos+1);

    if(x.empty()){
		throw runtime_error( BADREQUEST );
    }
    return x;
}


string findGetValue( string word , string &str , char delim , char message_delim ){
    str = delim + str + delim;
    word = delim + word + delim;

    size_t pos = str.find(word);
    if(pos == string::npos){
		throw runtime_error(BADREQUEST);
    }
    string str_r = str.substr(pos + word.length());
    string str_l = str.substr(0 , pos);
    string value = divString( str_r , delim , message_delim);
    str = str_l + str_r;
    return value;
}

bool isempty(string s , char delim){
    if(s.empty())
        return true;
    for(char c : s){
        if( c != delim)
            return false;
    }
    return true;
}


int getNatrualNumb(string s){
    try{
        size_t pos;
        if(s.length() >= 10)
            throw runtime_error(BADREQUEST);
        int x = stoi(s, &pos);
        if(x <= 0 || pos != s.length() )
            throw runtime_error(BADREQUEST);
        return x;
    }
    catch(invalid_argument & e){
        throw runtime_error(BADREQUEST);
    } 
}

int getWholeNumb(string s){
    try{
        size_t pos;
        if(s.length() >= 10)
            throw runtime_error(BADREQUEST);
        int x = stoi(s, &pos);
        if(x<0 || pos != s.length() )
            throw runtime_error(BADREQUEST);
        return x;
    }
    catch(invalid_argument & e){
        throw runtime_error(BADREQUEST);
    }
}


// int main(){
//     string input;
//     getline(cin, input);
// }