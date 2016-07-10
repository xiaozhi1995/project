#pragma once
#include <iostream>
#include <string>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <vector>
//#include <unistd.h>
#include "comm.h"
#include "udp_data.h"
#include "chat_window.h"

#define remote_ip  "127.0.0.1"
#define remote_port 8080

class udp_client{
	public:
		void init();
		void add_friend(const std::string &_win_f);
		void del_friend(const std::string &_win_f);
		udp_client(const std::string &_ip = remote_ip, const short &_port = remote_port);

		int recv_data(std::string &_out); // 1->1
		int send_data(std::string &_in);// 1->1

		~udp_client();

		std::vector<std::string> clif;
	private:
		std::string ip;
		short port;
		int sock;
};






