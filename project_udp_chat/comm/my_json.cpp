#include "my_json.h"

my_json::my_json()
{}

int my_json::serialize( Json::Value &_val, std::string &_out_str)
{
#ifdef _DEBUG_
	Json::StyledWriter _write;
#else
	Json::FastWriter _write;
#endif
	_out_str = _write.write(_val);
	return 0;
}

int my_json::deserialize( std::string &_in_str, Json::Value &_out_val)
{
	Json::Reader _read;
	if( _read.parse(_in_str, _out_val, false) ){
		return 0;
	}
	return 1;
}

my_json::~my_json()
{}


