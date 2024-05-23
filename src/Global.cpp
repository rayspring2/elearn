#include "Global.hpp"

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
    if( x .empty()){
		throw runtime_error( BADREQUEST );
    }
	if( input.size() == 0 || input[0] == delim)
    	return x;
	else{
		throw runtime_error(BADREQUEST);
	}
}


string findGetValue( string word , string &str , char delim , char message_delim ){
    size_t pos = str.find(word);
    if(pos == string::npos){
		throw runtime_error(BADREQUEST);
    }
    bool word_is_seperated = (pos == 0 || !isalnum(str[pos - 1])) &&
        (pos + word.length() == str.length() || !isalnum(str[pos + word.length()]));
    if (!word_is_seperated) {
        throw runtime_error(BADREQUEST);
    }
    string str_r = str.substr(pos + word.length());
    string str_l = str.substr(0 , pos);
    
    string value = divString( str_r , delim , message_delim);
	str = str_l + str_r;
    return value;
}