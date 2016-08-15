#include"common.h"
void enx(void* data,int len)
{
	for(int i=0;i<len;++i)
	{
		((char*)data)[i]^=8;
	}
}
void* transfer(void* arg)
{
	fd_thread* ftp=(fd_thread*)arg;
	char buf[1024];
	ssize_t _s=0;
	int in=ftp->in;
	int out=ftp->out;
	pthread_t pid=ftp->pid;
	while(1)
	{
		_s=recv(in,buf,sizeof(buf),0);
		if(_s<=0)
		{
			break;
		}
		else
		{
			_s=send(out,buf,_s,0);
			if(_s<=0)
				break;
		}
	}
	close(in);
	close(out);
	pthread_cancel(pid);
	return NULL;
}
