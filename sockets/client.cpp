#include"common.h"
int  proc_forward(int sock,char* rip,char* rport)
{
	sockaddr_in local;
	local.sin_family=AF_INET;
	local.sin_addr.s_addr=inet_addr(rip);
	local.sin_port=htons(atoi(rport));

	int out=socket(AF_INET,SOCK_STREAM,0);
	assert(out>=0);
	assert(0==connect(out,(sockaddr*)&local,sizeof(local)));
	
	 
	fd_thread th1(sock,out,0);
	fd_thread th2(out,sock,0);
	
	pthread_create(&th2.pid,NULL,transfer,&th1);
	pthread_create(&th1.pid,NULL,transfer,&th2);

	pthread_join(th1.pid,NULL);
	pthread_join(th2.pid,NULL);
	return 0;

}
int main(int argc,char* argv[])
{
	if(argc!=4)
	{
		printf("Usage:./server port remote_ip remote_port\n");
		return 1;
	}
	int listen_sock=socket(AF_INET,SOCK_STREAM,0);
	assert(listen_sock>=0);
	sockaddr_in local;
	local.sin_family=AF_INET;
	local.sin_port=htons(atoi(argv[1]));
	local.sin_addr.s_addr=INADDR_ANY;
	if(bind(listen_sock,(sockaddr*)&local,sizeof(local))==-1)
	{
		perror(strerror(errno));
		return 2;
	}
	if(listen(listen_sock,5)==-1)
	{
		perror(strerror(errno));
		return 3;
	}
	sockaddr_in client;
	socklen_t len=sizeof(client);
	while(1)
	{
		int new_sock=accept(listen_sock,(sockaddr*)&client,&len);
		if(new_sock==-1)
		{
			continue;
		}
		else
		{
			pid_t id=fork();
			assert(id>=0);
			if(id>0)
			{
				wait(NULL);
			}
			else
			{
				pid_t tid=fork();
				assert(tid>=0);
				if(tid>0)
				{
					exit(0);
				}
				else
				{
					return proc_forward(new_sock,argv[2],argv[3]);
				}
			}
		}
	}
	return 0;
}
