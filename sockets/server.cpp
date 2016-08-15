#include"common.h"

int handle_accept(int sock)
{
	req _quest;
	ssize_t _s;
	_s=recv(sock,&_quest,sizeof(_quest),0);
	if(_s<=0)
	{
		perror(strerror(errno));
		return -1;
	}
	else
	{
		assert(_quest.ver==5);
		char* method_list=new char[_quest.method_n];
		recv(sock,method_list,_quest.method_n,0);
		rep _reply;
		_reply.ver=_quest.ver;
		_reply.method=0;
		send(sock,&_reply,sizeof(_reply),0);
		delete[] method_list;
	}
	mesq _msq;
	_s=recv(sock,&_msq,sizeof(_msq),0);
	sockaddr_in _sock_ip;
	if(_s<=0)
	{
		perror(strerror(errno));
		return -1;
	}
	else
	{
		assert(_msq.ver==5&&_msq.cmd==1&&_msq.rsv==0);
		int atyp=_msq.atyp;
		_sock_ip.sin_family=AF_INET;
		if(atyp==1)//ipv4
		{
			recv(sock,&_sock_ip.sin_addr.s_addr,sizeof(in_addr_t),0);
		}
		else if(atyp==3)
		{
			char length;
			recv(sock,&length,sizeof(length),0);

			char domain[1024];
			recv(sock,domain,length,0);
			domain[length]='\0';

			hostent *host=gethostbyname(domain);
			assert(host&&host->h_addrtype==AF_INET&&host->h_length>=1);

			memcpy(&_sock_ip.sin_addr.s_addr,host->h_addr_list[0],sizeof(_sock_ip.sin_addr.s_addr));
		}
		short port;
		recv(sock,&port,sizeof(port),0);
		memcpy(&_sock_ip.sin_port,&port,sizeof(_sock_ip.sin_port));
		cout<<"ready connect"<<endl;
	}
	
	int out=socket(AF_INET,SOCK_STREAM,0);
	assert(out>=0);
	assert(0==connect(out,(sockaddr*)&_sock_ip,sizeof(_sock_ip)));
	
	mesp mep;
	mep.ver=5;
	mep.rep=0;
	mep.rsv=0;
	mep.atyp=1;

	sockaddr_in local;
	socklen_t len=sizeof(local);
	assert(getsockname(out,(sockaddr*)&local,&len));
	memcpy(&mep.ip,&local.sin_addr.s_addr,sizeof(mep.ip));
	memcpy(&mep.port,&local.sin_port,sizeof(mep.port));
	 
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
	if(argc!=2)
	{
		printf("Usage:./server port\n");
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
					return handle_accept(new_sock);
				}
			}

		}
	}
	return 0;
}
