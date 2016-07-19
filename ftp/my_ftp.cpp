#include"my_ftp.h"
const int SIZE=1024;
int interact(int sock,const char* input,char* output)
{
	int ret=send(sock,input,strlen(input),0);
	if(ret<0)
	{
		perror(strerror(errno));
		return ret;
	}
	ret=recv(sock,output,SIZE,0);
	if(ret<0)
	{
		perror(strerror(errno));
		return ret;
	}
	output[ret]='\0';
	return 0;
}
int start_listen(int sock,sockaddr_in& local)
{
	int server=socket(AF_INET,SOCK_STREAM,0);
	if(server<0)
	{
		perror(strerror(errno));
		return -1;
	}
	socklen_t len=sizeof(local);
	int ret=getsockname(sock,(sockaddr*)&local,&len);
	if(ret<0)
	{
		perror("getsockname");
		return -1;
	}
	local.sin_port=0;//random
	ret=bind(server,(sockaddr*)&local,sizeof(local));
	if(ret<0)
	{
		perror("bind");
		return -1;
	}
	ret=listen(server,5);
	if(ret<0)
	{
		perror("listen");
		return -1;
	}
	ret=getsockname(server,(sockaddr*)&local,&len);
	if(ret<0)
	{
		perror("getsockname");
		return -1;
	}
	return server;
}
int recv_data(int data_sock,const char* filename)
{
	FILE* fp=fopen(filename,"w");
	if(fp==NULL)
	{
		perror("fopen");
		return -1;
	}
	ssize_t _s=-1;
	while(1)
	{
		char buf[SIZE];
		_s=recv(data_sock,buf,SIZE,0);
		if(_s<0)
		{
			perror("recv");
			close(data_sock);
			return _s;
		}
		else if(_s==0)
		{
			close(data_sock);
			fclose(fp);
			return 0;
		}
		if(fwrite(buf,_s,1,fp)!=1)
		{
			close(data_sock);
			fclose(fp);
			return -1;
		}
	}
}
int main(int argc,char* argv[])
{
	if(argc!=5)
	{
		cout<<"Usage: [ip] [user] [pass] [filename]"<<endl;
		return -1;
	}
	int sock=socket(AF_INET,SOCK_STREAM,0);
	if(sock<0)
	{
		perror("socket");
		return -1;
	}
	sockaddr_in server_addr;
	server_addr.sin_family=AF_INET;
	server_addr.sin_addr.s_addr=inet_addr(argv[1]);
	server_addr.sin_port=htons(21);
	int ret=connect(sock,(sockaddr*)&server_addr,sizeof(server_addr));
	if(ret<0)
	{
		perror("connect");
		return 2;
	}
	char buf[SIZE];
	char output[SIZE];
	ssize_t _s=recv(sock,buf,SIZE,0);
	if(_s<0)
	{
		perror("recv");
		return _s;
	}
	buf[_s]='\0';
	cout<<buf<<endl;
	sprintf(buf,"USER %s\r\n",argv[2]);
	if(interact(sock,buf,output)<0)
	{
		perror("USER");
		return -1;
	}
	cout<<output<<endl;
	sprintf(buf,"PASS %s\r\n",argv[3]);
	if(interact(sock,buf,output)<0)
	{
		perror("PASS");
		return -1;
	}
	cout<<output<<endl;
	
	sockaddr_in local_addr;
	int listen_sock=start_listen(sock,local_addr);
	if(listen_sock<0)
	{
		perror("start_listen");
		return -1;
	}
	unsigned char* _ip=(unsigned char*)&local_addr.sin_addr.s_addr;
	unsigned short _port=ntohs(local_addr.sin_port);
	sprintf(buf, "PORT %d,%d,%d,%d,%d,%d\r\n", _ip[0], _ip[1], _ip[2],_ip[3],_port/256,_port%256);
	cout<<buf<<endl;
	if(interact(sock,buf,output)<0)
	{
		cout<<"interact"<<endl;
		return -1;
	}
	cout<<output<<endl;
	sprintf(buf,"RETR %s\r\n",argv[4]);
	if(interact(sock,buf,output)<0)
	{
		cout<<"interact"<<endl;
		return -1;
	}
	cout<<output<<endl;
	sockaddr_in ser_addr;
	socklen_t ser_len=sizeof(ser_addr);
	int data_sock=accept(listen_sock,(sockaddr*)&ser_addr,&ser_len);
	if(data_sock<0)
	{
		perror("accept");
		return -1;
	}
	close(listen_sock);
	ret=recv_data(data_sock,argv[4]);
	if (ret < 0) {
		cout << "recv data error" << endl;
		}
	close(sock);
	return 0;
}
