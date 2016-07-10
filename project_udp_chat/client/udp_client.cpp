#include "udp_client.h"

using namespace std;

udp_client::udp_client(const string &_ip, const short &_port)
	:ip(_ip)
	,port(_port)
	,sock(-1)
{}

void udp_client::init()
{
	sock = socket(AF_INET, SOCK_DGRAM, 0);
	if( sock < 0 ){
		print_log(strerror(errno), __FUNCTION__, __LINE__);
		exit(1);
	}
}

int udp_client::recv_data(std::string &_out) // 1->1
{
	struct sockaddr_in server;
	socklen_t len = sizeof(server);
	char buf[_SIZE_];
	buf[0] = '\0';
	ssize_t _s = recvfrom(sock, buf, sizeof(buf)-1, 0, (struct sockaddr*)&server, &len);
	if( _s > 0 ){
		buf[_s] = '\0';
		_out = buf;
	}else if( _s == 0 ){
		const char *msg = "client is close";
		print_log(msg , __FUNCTION__, __LINE__);
	}else{
		print_log(strerror(errno), __FUNCTION__, __LINE__);
	}
	return _s;
}

int udp_client::send_data(std::string &_in)// 1->1
{
	struct sockaddr_in server;
	server.sin_family = AF_INET;
	server.sin_port  = htons(port);
	server.sin_addr.s_addr = inet_addr(ip.c_str());
	socklen_t len = sizeof(server);

	ssize_t _s = sendto(sock, _in.c_str(), _in.size(), 0, (struct sockaddr*)&server, len);
	if( _s < 0 ){
		print_log(strerror(errno), __FUNCTION__, __LINE__);
	}
	return _s;
}

void udp_client::del_friend(const std::string &_win_f)
{
	std::vector<std::string>::iterator _iter = clif.begin();
	for( ; _iter != clif.end(); ){
		if( *_iter == _win_f ){
			_iter = clif.erase(_iter);
			break;
		}else{
			_iter++;
		}
	}
}
void udp_client::add_friend(const std::string &_win_f)
{
	std::vector<std::string>::iterator _iter = clif.begin();
	for( ; _iter != clif.end(); ++_iter){
		if( *_iter == _win_f ){
			return;
		}
	}
	clif.push_back(_win_f);
}

udp_client::~udp_client()
{
	if( sock > 0 ){
		close(sock);
	}
}



