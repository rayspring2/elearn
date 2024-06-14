#include "University.hpp"

University::University(char* argv[]){
	system.readData(argv);
    SystemHandler::setSystem(system);
    mapServerPaths(server);
}
void University::mapServerPaths(Server& server) {
    server.setNotFoundErrPage("static/404.html");
    server.get("/", new ShowPage("static/home.html"));
    server.get("/home.png", new ShowImage("static/home.png"));
    
    server.get("/loggedin", new ShowPage("static/loggedin.html"));
    server.get("/login", new ShowPage("static/logincss.html"));
    server.post("/login", new LoginHandler());
    
    server.get("/personal_page", new showPersonalPageHandler());
    server.get("/admin_home", new ShowPage("static/admin_home.html"));
    server.get("/professor_home", new ShowPage("static/professor_home.html"));
    server.get("/student_home", new ShowPage("static/student_home.html"));
    server.get("/student_home/user", new studentGetinfoHandler());

    server.get("/profile_default.png", new ShowImage("pic/profile_default.png"));
    
    server.get("/up", new ShowPage("static/upload_form.html"));
    server.post("/up", new UploadHandler());
    // server.get("/colors", new ColorHandler("template/colors.html"));
    server.get("/music", new ShowPage("static/music.html"));
    server.get("/music/moonlight.mp3", new ShowFile("static/moonlight.mp3", "audio/mpeg"));
}

void University::run(){
	server.run();
}