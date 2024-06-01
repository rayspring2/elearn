#pragma once
#include "Global.hpp"
#include "Post.hpp"

class ChannelPost : public Post{
private:
	int sender_id;
public:
	ChannelPost(int sender_id, int id, string title, string message, string pic_path);	
	int getSenderId();	
};