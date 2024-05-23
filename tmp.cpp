#include <iostream>
#include <sstream>
#include <fstream>
#include <istream>
#include <vector>
#include <exception>
#include <stdexcept>
using namespace std;
const string BADREQUEST = "baddddd";

vector<vector<string>> readCSVLine( string line ){
    cerr << "line---------------------------------\n*****" << line <<endl;
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
            //
            cerr << (int)s[s.size()-1] << "+++" << s[s.size()-1] <<  endl;
            s = "";
        }
		
        if( x == ',' || x == '\n' ){
            input.push_back(sametype);
            sametype.clear();
        }
    }
	sametype.push_back(s);
    cerr << (int)s[s.size()-1] << "+++" << s[s.size()-1] <<  endl;
	input.push_back(sametype);
    //cerr << "line---------------------------------\n";
    return input;
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