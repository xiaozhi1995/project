#include"udp_client.h"
udp_client _cl;
udp_data ud;
void* draw_header(void* arg)
{
	chat_window* _win=(chat_window*)arg;
	_win->create_header();
	string _line="HELLO WORLD";
	int _max_y;
	int _max_x;
	getmaxyx(_win->header,_max_y,_max_x);

	int _y=_max_y/2;
	int _x=1;
	while(1)
	{
		_win->put_str_to_win(_win->header,_y,_x,_line);
		_win->fflush_win(_win->header);
		usleep(10000);
		_x++;
		_x%=_max_x;
		_win->clear_win_line(_win->header,_y,2);
		_win->fflush_win(_win->header);
		usleep(10000);
	}

}
void* draw_output(void* arg)
{
	chat_window* _win=(chat_window*)arg;
	_win->create_output();
	string outmsg;
	string show_msg;
	string list;
	int _max_y;
	int _max_x;
	getmaxyx(_win->header,_max_y,_max_x);

	int _y=1;
	int _x=1;
    string _name;
    string _msg;
    string _school;
    string _cmd;

	while(1)
	{
		usleep(10000);
		_win->fflush_win(_win->output);

	    _cl.recv_data(outmsg);
		ud.data_to_value(_name,_msg,_school,_cmd,outmsg);
		
		show_msg=_name+"_"+_school+":"+_msg;

		_win->put_str_to_win(_win->output,_y,_x,show_msg);

		_y++;
		if(_y==_max_y)
		{
			_win->clear_win_line(_win->output,1,_max_y-2);
			_y=1;
		}
		usleep(10000);
		_win->fflush_win(_win->output);
	}
}
void* draw_friends_list(void* arg)
{
	chat_window* _win=(chat_window*)arg;
	_win->create_friends_list();

	int _max_y;
	int _max_x;
	getmaxyx(_win->header,_max_y,_max_x);

	int _y=1;
	int _x=1;
	while(1)
	{
		usleep(1000000);
		_y=1;
		_win->fflush_win(_win->friends_list);

		_win->clear_win_line(_win->friends_list,1,_y);
	}
}
void* draw_input(void* arg)
{
	chat_window* _win=(chat_window*)arg;
	_win->create_input();
	string _line="please input#";
	int _max_y;
	int _max_x;
	getmaxyx(_win->input,_max_y,_max_x);
    string _name=ud.nick_name;
    string _msg;
    string _school=ud.school;
    string _cmd=ud.cmd;
	string _out;//send msg jsoncpp
	string list;
	while(1)
	{
		usleep(1000000);
		_win->put_str_to_win(_win->input,1,1,_line);
		_win->fflush_win(_win->input);
		_msg=_win->get_str_from_win(_win->input);
		list=_name+"_"+_school;
		if(_msg=="quit"||_msg=="q")
		{
		}
		ud.data_to_string(_name,_msg,_school,_cmd,_out);
		_cl.send_data(_out);
		
		_win->clear_win_line(_win->input,1,2);
		usleep(1000);
		_win->put_str_to_win(_win->input,1,1,_line);
		_win->fflush_win(_win->input);
	}
}
//int main()
//{
//	chat_window _wi;
//	pthread_t th,to,tf,ti;
//	pthread_create(&th,NULL,draw_header,(void*)&_wi);
//	pthread_create(&to,NULL,draw_output,(void*)&_wi);
//	pthread_create(&tf,NULL,draw_friends_list,(void*)&_wi);
//	pthread_create(&ti,NULL,draw_input,(void*)&_wi);
//	pthread_join(th,NULL);
//	pthread_join(to,NULL);
//	pthread_join(tf,NULL);
//	pthread_join(ti,NULL);
//	return 0;
//}


int main()
{
	_cl.init();
	string _name;
	cout<<"please input name: ";
	cin>>_name;
	string _msg;
	cout<<"please input msg: ";
	cin>>_msg;
	string _school;
	cout<<"please input school: ";
	cin>>_school;
	string _cmd;
	cout<<"please input cmd: ";
	cin>>_cmd;
	string _out;
//	_name="rz";
	ud.data_to_string(_name,_msg,_school,_cmd,_out);
	_cl.send_data(_out);
	chat_window _wi;
	pthread_t th,to,tf,ti;
	pthread_create(&th,NULL,draw_header,(void*)&_wi);
	pthread_create(&to,NULL,draw_output,(void*)&_wi);
	pthread_create(&tf,NULL,draw_friends_list,(void*)&_wi);
	pthread_create(&ti,NULL,draw_input,(void*)&_wi);
	pthread_join(th,NULL);
	pthread_join(to,NULL);
	pthread_join(tf,NULL);
	pthread_join(ti,NULL);
//	_name="";

}
//int main()
//{
//	udp_client _cl;
//	_cl.init();
//	udp_data ud;
//	string _name;
//	cout<<"please input name: ";
//	cin>>_name;
//	string _msg;
//	cout<<"please input msg: ";
//	cin>>_msg;
//	string _school;
//	cout<<"please input school: ";
//	cin>>_school;
//	string _cmd;
//	cout<<"please input cmd: ";
//	cin>>_cmd;
//	string _out;
////	_name="rz";
//	ud.data_to_string(_name,_msg,_school,_cmd,_out);
//	_cl.send_data(_out);
////	_name="";
////	ud.data_to_value(_name,_msg,_school,_cmd,_out);
////	cout<<_out<<endl;
////	cout<<_name;
//	_out="";
//    _cl.recv_data(_out);
//	cout<<_out<<endl;
//    ud.data_to_value(_name,_msg,_school,_cmd,_out);
//    
//    cout<<"name: "<<_name<<endl;
//    cout<<"msg: "<<_msg<<endl;
//    cout<<"school: "<<_school<<endl;
//	  cout<<"cmd: "<<_cmd<<endl;
//	while(1)
//	{
//		cout<<"please input msg";
//		cin>>_msg;
//		ud.data_to_string(_name,_msg,_school,_cmd,_out);
//
//		_cl.send_data(_out);
//		_out="";
//		_cl.recv_data(_out);
//		ud.data_to_value(_name,_msg,_school,_cmd,_out);
//
//		cout<<"name: "<<_name<<endl;
//		cout<<"msg: "<<_msg<<endl;
//		cout<<"school: "<<_school<<endl;
//		cout<<"cmd: "<<_cmd<<endl;
//	}
//}
