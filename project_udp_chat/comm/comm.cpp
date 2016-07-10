#include "comm.h"

using namespace std;

void print_log(const char *msg, const char *fun, int line)
{
	//time
	//printf("%s : [ %s ] [ %d ]\n", msg, fun, line);
#ifdef _DEBUG_
	cout<<msg<<" : [ "<<fun<<" ] ["<<line<<" ]"<<endl;
//#else
	
#endif
}
