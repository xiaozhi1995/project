#include"udp_server.h"
int main()
{
	udp_server _se;
	_se.init();
	_se.recv_data();
	_se.broadcast();
	return 0;
}
