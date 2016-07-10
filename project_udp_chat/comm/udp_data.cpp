#include "udp_data.h"

udp_data::udp_data()
{}
void udp_data::to_string(std::string &_in_nick_name,std::string &_in_msg, std::string &_in_school, std::string &_in_cmd, std::string &_out_str)
{
	nick_name = _in_nick_name;
	msg       = _in_msg;
	school    = _in_school;
	cmd       = _in_cmd;

	Json::Value root;
	root["nick_name"] = nick_name;
	root["msg"]       = msg;
	root["school"]    = school;
	root["cmd"]       = cmd;
	my_json::serialize(root, _out_str);
}

void udp_data::to_val(std::string &_out_nick_name,std::string &_out_msg, std::string &_out_school, std::string &_out_cmd, std::string &_in_str)
{
	Json::Value _val;
	my_json::deserialize( _in_str, _val);

	_out_nick_name = _val["nick_name"].asString();
	_out_msg       = _val["msg"].asString();
	_out_school    = _val["school"].asString();
	_out_cmd       = _val["cmd"].asString();

	nick_name = _out_nick_name;
	msg       = _out_msg;
	school    = _out_school;
	cmd       = _out_cmd;
}

udp_data::~udp_data()
{}

//int main()
//{
//	std::string nick_name;// = "flypig";
//	std::string msg      ;// = "hello world";
//	std::string school   ;// = "XPU";
//	std::string cmd      ;// = "None";
//
//	udp_data _data;
////	std::string str;
////
////	_data.to_string(nick_name, msg, school, cmd, str);
////	std::cout<<str<<std::endl;
//
//
//	std::string _in_str = "{\"cmd\":\"None\",\"msg\":\"hello world\",\"nick_name\":\"flypig\",\"school\":\"XPU\"}";
//	_data.to_val(nick_name, msg, school, cmd, _in_str);
//	std::cout<<nick_name<<std::endl;
//	std::cout<<msg<<std::endl;
//	std::cout<<school<<std::endl;
//	std::cout<<cmd<<std::endl;
//
//}






