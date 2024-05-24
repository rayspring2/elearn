#include "../include/Global.hpp"

vector<vector<string>> readCSVLine( string line ){
    //cerr << "line---------------------------------\n*****" << line <<endl;
    vector<vector<string>> input;
    vector<string> sametype;
    string s = "";
    while( !line.empty() ){
        char x = line[0];
        line.erase(line.begin());
        if( x != ';' && x != ',' && x != '\n' ){
            s = s + x;
            //cerr <<s<<endl;
			continue;
        }   
        if( x == ';' || x == ',' || x == '\n'){
            sametype.push_back(s);
            //
            //cerr << (int)s[s.size()-1] << "+++" << s[s.size()-1] <<  endl;
            s = "";
        }
		
        if( x == ',' || x == '\n' ){
            input.push_back(sametype);
            sametype.clear();
        }
    }
	sametype.push_back(s);
    //cerr << (int)s[s.size()-1] << "+++" << s[s.size()-1] <<  endl;
	input.push_back(sametype);
    //cerr << "line---------------------------------\n";
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

// int main(){
//     string input;
//     getline(cin, input);
//     cout << divString(input)  <<"|"<< endl;

// }