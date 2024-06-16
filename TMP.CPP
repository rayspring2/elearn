#include <bits/stdc++.h>

using namespace std;

int main(){
    string body="";
    body +=  "<div class='post'>";
        body += "<div class='post-title'>" "fgfgfg" "</div>";
		body += "<div class='post-message'>"  "gggggg"  "</div>";
		
            body += "<img src=\"/post?post-id="
			+ to_string(222) + "&user_id=" "11111"  "\" alt='Post Image'>";
		
		body += "</div>";
    cout << body << endl;
}