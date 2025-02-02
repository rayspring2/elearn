#pragma once
#include "Global.hpp"
#include "System.hpp"
#include "../server/server.hpp"

class SystemHandler: public RequestHandler{
protected:
	static System system;
public:
	static void setSystem(System system);
	
};

class LoginHandler : public SystemHandler {
public:
    Response* callback(Request*) override;
};

class showPersonalPageHandler : public SystemHandler{
public:
    Response* callback(Request*) override;
};

class studentGetinfoHandler : public SystemHandler {
public:
    Response* callback(Request*) override;
};

class UploadHandler : public SystemHandler {
public:
    Response* callback(Request*) override;
};

class profileImageHandler : public SystemHandler {
public:
    Response* callback(Request*) override;

};

class showPostsHandler : public SystemHandler {
public:
    Response* callback(Request*) override;

};

class postUploadHandler : public SystemHandler {
public:
    Response* callback(Request*) override;

};

class showPostbyIdHandler : public SystemHandler {
public:
    Response* callback(Request*) override;

};

class showOfferedCoursesHandler : public SystemHandler {
public:
    Response* callback(Request*) override;

};

class addCourseHandler : public SystemHandler {
public:
    Response* callback(Request*) override;

};

class logoutHandler : public SystemHandler{
public:
    Response* callback(Request*) override;

};

class showStudentCourseHandler : public SystemHandler{
public:
    Response* callback(Request*) override;

};
class deleteCourseHandler : public SystemHandler{
public:
    Response* callback(Request*) override;

};

class addStudentCourseHandler : public SystemHandler{
public:
    Response* callback(Request*) override;

};

class findUserHandler : public SystemHandler{
public:
    Response* callback(Request*) override;

};

class getStudentPageInfoHandler : public SystemHandler{
public:
    Response* callback(Request*) override;

};

class getProfessorPageInfoHandler : public SystemHandler{
public:
    Response* callback(Request*) override;

};

class getAdminPageInfoHandler : public SystemHandler{
public:
    Response* callback(Request*) override;

};
