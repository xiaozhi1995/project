#pragma once

#include <iostream>
#include <string>
#include <json/json.h>
//#include "json.h"

class my_json{
	public:
		my_json();
        static int serialize( Json::Value &_val, std::string &_out_str);
        static int deserialize( std::string &_in_str, Json::Value &_out_val);
		~my_json();
};
