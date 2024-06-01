#include "ChannelPost.hpp"

ChannelPost::ChannelPost(int sender_id, int id, string title, string message, string pic_path):
sender_id(sender_id), Post(id, title, message, pic_path){}

int ChannelPost::getSenderId(){
	return sender_id;
}	

