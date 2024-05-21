#include "Global.hpp"

vector<vector<string>> readCSVLine( string line ){
	stringstream streamline(line);
    //cerr << "line---------------------------------\n*****" << line <<endl;
    char x;
    vector<vector<string>> input;
    vector<string> sametype;
    string s = "";
    while( streamline.get(x) ){
        
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