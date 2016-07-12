#include"my_ftp.h"
void Usage(const char* proc)
{
	cout<<"Usage:"<<proc<<" [ip] [username] [passwd] [filename]"<<endl;
}
int main(int argc,char* argv[])
{
	if(argc!=5)
	{
		Usage(argv[0]);
		exit(1);
	}
	int sock=socket(AF_INET,SOCK_STREAM,0);
	struct sockaddr_in server;
	server.sin_family=AF_INET;
	server.sin_port=htons(21);
	server.sin_addr.s_addr=inet_addr(argv[1]);
	socklen_t len=sizeof(server);


	if(connect(sock,(struct sockaddr*)&server,len)<0)
	{
		perror(strerror(errno));
		exit(2);
	}
	char buf[1024];
	char _msg[1024];
	ssize_t _s;
	memset(buf,'\0',sizeof(buf));
	memset(_msg,'\0',sizeof(_msg));
	_s=recv(sock,buf,sizeof(buf)-1,0);
	if(_s==0)
	{
		cout<<"server is close";
		exit(-1);
	}
	else if(_s<0)
	{
		perror(strerror(errno));
		exit(-2);
	}
	cout<<buf<<endl;
	/* 命令 ”USER username\r\n” */	
	sprintf(_msg,"USER %s\r\n",argv[2]);
	send(sock,_msg,strlen(_msg),0);
	memset(buf,'\0',sizeof(buf));
	recv(sock,buf,sizeof(buf)-1,0);
	cout<<buf<<endl;
	
	/* 命令 ”PASS passwd\r\n” */	
	sprintf(_msg,"PASS %s\r\n",argv[3]);
	send(sock,_msg,strlen(_msg),0);
	memset(buf,'\0',sizeof(buf));
	recv(sock,buf,sizeof(buf)-1,0);
	cout<<buf<<endl;


	int ser_sock=socket(AF_INET,SOCK_STREAM,0);
	if(ser_sock<0)
	{
		perror(strerror(errno));
		exit(4);
	}
	struct sockaddr_in local;
	socklen_t l_len=sizeof(local);
	local.sin_family=AF_INET;
	local.sin_port=0;
	if(getsockname(sock,(struct sockaddr*)&local,&l_len)<0)
	{
		perror(strerror(errno));
		exit(3);
	}
	bind(ser_sock,(struct sockaddr*)&local,l_len);
	listen(ser_sock,5);
	if(getsockname(ser_sock,(struct sockaddr*)&local,&l_len)<0)
	{
		perror(strerror(errno));
		exit(3);
	}
//	cout<<"get sockname"<<endl;


	//ip port
	unsigned char* _addr=(unsigned char*)&local.sin_addr.s_addr;
	short _port=ntohs(local.sin_port);
	sprintf(_msg,"PORT %d,%d,%d,%d,%d,%d\r\n",_addr[0],_addr[1],_addr[2],_addr[3],_port/256,_port%256);
	send(sock,_msg,strlen(_msg),0);
	
	cout<<"send success"<<endl;
		
	
	memset(buf,'\0',sizeof(buf));
	recv(sock,buf,sizeof(buf)-1,0);
	cout<<buf<<endl;
	cout<<"port reply"<<endl;
	//file name
	sprintf(_msg,"RETR %s\r\n",argv[4]);
	send(sock,_msg,strlen(_msg),0);
	
	//reply
	memset(buf,'\0',sizeof(buf));	
	recv(sock,buf,sizeof(buf)-1,0);
	cout<<buf<<endl;
	//connect
	memset(buf,'\0',sizeof(buf));
	recv(sock,buf,sizeof(buf)-1,0);
	cout<<buf<<endl;
	
	
	accept(sock,(struct sockaddr*)&local,&l_len);
	//send file
	FILE* fp=fopen("tmp","w");
	if(fp==NULL)
	{
		perror(strerror(errno));
		exit(4);
	}
	ssize_t _fs=-1;
	while((_fs=recv(sock,buf,sizeof(buf)-1,0))>0)
	{
		fwrite(buf,_fs,1,fp);
		memset(buf,'\0',sizeof(buf));
	}

	sprintf(_msg,"BYE\r\n");
	send(sock,_msg,strlen(_msg),0);
//	sprintf(_msg,"PASV\r\n");
//	send(sock,_msg,strlen(_msg),0);
//	/* 客户端告诉服务器用被动模式 */
//	
//	memset(buf,'\0',sizeof(buf));
//	recv(sock,buf,sizeof(buf)-1,0);
//	/*客户端接收服务器的响应码和新开的端口号，
//	* 正常为 ”227 Entering passive mode (<h1,h2,h3,h4,p1,p2>)” */
//
//	cout<<buf<<endl;
	return 0;
}
