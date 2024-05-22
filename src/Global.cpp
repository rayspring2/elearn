#include "Global.hpp"

vector<vector<string>> readCSVLine( string line ){
    //cerr << "line---------------------------------\n*****" << line <<endl;
    char x;
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
            s = "";
        }
		
        if( x == ',' || x == '\n' ){
            input.push_back(sametype);
            sametype.clear();
        }
    }
	sametype.push_back(s);
	input.push_back(sametype);
    //cerr << "line---------------------------------\n";
    return input;
}


string divString( string &input , char delim){
    string x = "";
    while( input != ""){
        if(input[0] == ' ')
            input.erase(input.begin());
        else
            break;
    }
    while(input != "") {
        if( input[0] == delim )
            break;
        x = x + input[0];
        input.erase(input.begin());
    }
    if( x == ""){
        throw runtime_error( BADREQUEST );
    }
    return x;
}
