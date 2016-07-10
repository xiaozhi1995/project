#include "udp_client.h"

using namespace std;

udp_client *cli_p = NULL;
std::string nick_name;
std::string school;

static void usage(const char *proc)
{
	std::cout<<"Usage "<<proc<<" [remote_ip] [remote_port]"<<std::endl;
}

static void *draw_header(void *arg)
{
	chat_window *winp = (chat_window*)arg;
	winp->create_header();

	bool done = false;
	const std::string _line = "Hello world & bit";
	int _max_y;
	int _max_x;
	getmaxyx(winp->header, _max_y, _max_x);

	int _y = _max_y/2;
	int _x = 0;

	while( !done ){
		winp->put_str_to_win(winp->header, _y, _x, _line);
		winp->fflush_win(winp->header);
		usleep(100000);
		winp->clear_win_line(winp->header,_y, 1);
		_x++;
		_x %= _max_x;
	}
}

static void *draw_output(void *arg)
{
	std::string msg;
	chat_window *winp = (chat_window*)arg;
	winp->create_output();
	int _max_y;
	int _max_x;
	getmaxyx(winp->output, _max_y, _max_x);

	winp->create_friends_list();
	int _max_fy;
	int _max_fx;
	getmaxyx(winp->friends_list, _max_fy, _max_fx);

	udp_data data;
	std::string _nick_name;
	std::string _msg;
	std::string _school;
	std::string _cmd;
	std::string _win_out;
	std::string _win_f;

	bool done = false;
	int _y = 1;
	while( !done ){
		cli_p->recv_data(msg); // 1->1
		data.to_val(_nick_name, _msg, _school, _cmd, msg);
		//name-school# msg
		_win_out = _nick_name;
		_win_out += "-";
		_win_out += _school;

		_win_f =  _win_out;

		_win_out += "# ";
		_win_out += _msg;

		cli_p->add_friend(_win_f);
		if( _cmd == "QUIT" ){
			cli_p->del_friend(_win_f);
		}

		winp->put_str_to_win(winp->output, _y++, 3, _win_out);
		//usleep(10000);
		if( _y >= _max_y ){
			_y=1;
			winp->clear_win_line(winp->output, 1, _max_y-1);
		}
		winp->fflush_win(winp->output);
		
		int size = (cli_p->clif).size();
		int page = size/(_max_fy-3);
		int mode = size%(_max_fy-3);
		if(mode != 0){
			page++;
		}
		int i = 0;
		while( i < size){
			winp->put_str_to_win(winp->friends_list, ++i, 3, cli_p->clif[i]);
		}
		winp->fflush_win(winp->friends_list);
	}
}

//static void *draw_friends_list(void *arg)
//{
//	chat_window *winp = (chat_window*)arg;
//	winp->create_friends_list();
//
//	bool done = false;
//	while( !done ){
//		winp->fflush_win(winp->friends_list);
//		usleep(1000000);
//	}
//}

static void *draw_input(void *arg)
{
	chat_window *winp = (chat_window*)arg;
	winp->create_input();
	std::string _line = "Please Enter# ";
	int _max_y;
	int _max_x;
	getmaxyx(winp->input, _max_y, _max_x);

	std::string _cmd = "None";
	udp_data _data;
	std::string _out;

	bool done = false;
	while( !done ){
		winp->put_str_to_win(winp->input, 1, 1, _line);
		winp->fflush_win(winp->input);
		std::string _in = winp->get_str_from_win(winp->input);
		winp->clear_win_line(winp->input,1, 1);

		if( _in == "quit" || _in == "q"){
			_cmd="QUIT";
			_data.to_string(nick_name, _in, school, _cmd, _out);
			cli_p->send_data(_out);
			exit(0);
		}
		_data.to_string(nick_name, _in, school, _cmd, _out);
		cli_p->send_data(_out);

		usleep(1000);
	}
}

int main(int argc, char *argv[])
{
	if( argc != 3 ){
		usage(argv[0]);
		exit(1);
	}
	std::string _remote_ip = argv[1];
	short _remote_port = atoi(argv[2]);

	std::cout<<"Please Enter Your Nick_name: ";
	fflush(stdout);
	std::cin>>nick_name;
	std::cout<<"Please Enter Your School: ";
	fflush(stdout);
	std::cin>>school;

	udp_client _cli(_remote_ip, _remote_port);
	_cli.init();
	cli_p = &_cli;

	chat_window _win;

	pthread_t th, to, ti, tf;
	pthread_create(&th, NULL, draw_header, (void*)&_win);
	pthread_create(&to, NULL, draw_output, (void*)&_win);
	//pthread_create(&tf, NULL, draw_friends_list, (void*)&_win);
	pthread_create(&ti, NULL, draw_input, (void*)&_win);

	pthread_join(th, NULL);
	pthread_join(to, NULL);
	//pthread_join(tf, NULL);
	pthread_join(ti, NULL);
//	//udp_client _cli;
//	std::string cmd = "None";
//	std::string msg;
//	std::string _ser_str;
//
//
//	char buf[_SIZE_];
//	std::string _out;
//	while(1){
//		cout<<"Please Enter# ";
//		fflush(stdout);
//		memset(buf, '\0', sizeof(buf));
//		ssize_t _s = read(0, buf, sizeof(buf)-1);
//		if( _s > 0 ){
//			buf[_s-1] = '\0';
//			msg = buf;
//
//			_data.to_string(nick_name, school, msg, cmd, _ser_str);
//			std::cout<<_ser_str<<std::endl;
//
//			_cli.send_data(_ser_str);
//
//			_cli.recv_data(_out);
//			std::cout<<"server echo: "<<_out<<std::endl;
//		}
//	}

	return 0;
}



