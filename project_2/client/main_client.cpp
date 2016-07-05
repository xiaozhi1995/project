#include"udp_client.h"
int main()
{
	string str="helloworld";
	udp_client _cl;
	_cl.init();
	_cl.send_data(str);
	_cl.recv_data(str);
	cout<<"server: "<<str<<endl;
}
