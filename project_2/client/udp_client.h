#include<iostream>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<stdio.h>
#include<string.h>
#include<string>
#include<stdlib.h>
#include"comm.h"
#define _IP_ "127.0.0.1"
#define _PORT_ 8080
class udp_client
{
	public:
		udp_client(string _ip=_IP_,short _port=_PORT_);
		void init();
		int send_data(string& _in);
		int recv_data(string& _out);
		~udp_client();
	private:
		string ip;
		short port;
		int sock;
};
