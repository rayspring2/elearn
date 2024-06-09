#include "System.hpp"
#include "io.hpp"
#include "Server.hpp"
#include "Handler.hpp"
void mapServerPaths(Server& server) {
    server.setNotFoundErrPage("static/404.html");
    server.get("/", new ShowPage("static/home.html"));
    server.get("/home.png", new ShowImage("static/home.png"));
    // server.get("/rand", new RandomNumberHandler());
    server.get("/login", new ShowPage("static/logincss.html"));
    // server.post("/login", new LoginHandler());
    server.get("/up", new ShowPage("static/upload_form.html"));
    // server.post("/up", new UploadHandler());
    // server.get("/colors", new ColorHandler("template/colors.html"));
    server.get("/music", new ShowPage("static/music.html"));
    server.get("/music/moonlight.mp3", new ShowFile("static/moonlight.mp3", "audio/mpeg"));
}

int main(int argc , char* argv[]){
    Server server;
    System system;
    system.readData(argv);
    SystemHandler::setSystem(system);
    mapServerPaths(server);
    server.run();   
}