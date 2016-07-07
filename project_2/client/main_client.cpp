#include"udp_client.h"
int main()
{
	udp_client _cl;
	_cl.init();
	udp_data ud;
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
//	_name="";
//	ud.data_to_value(_name,_msg,_school,_cmd,_out);
//	cout<<_out<<endl;
//	cout<<_name;

    _cl.recv_data(_out);
    ud.data_to_value(_name,_msg,_school,_cmd,_out);
    
    cout<<"name: "<<_name<<endl;
    cout<<"msg: "<<_msg<<endl;
    cout<<"school: "<<_school<<endl;
    cout<<"cmd: "<<_cmd<<endl;
	while(1)
	{
		cout<<"please input msg";
		cin>>_msg;
		ud.data_to_string(_name,_msg,_school,_cmd,_out);

		_cl.send_data(_out);
		_cl.recv_data(_out);
		ud.data_to_value(_name,_msg,_school,_cmd,_out);

		cout<<"name: "<<_name<<endl;
		cout<<"msg: "<<_msg<<endl;
		cout<<"school: "<<_school<<endl;
		cout<<"cmd: "<<_cmd<<endl;
	}
}
