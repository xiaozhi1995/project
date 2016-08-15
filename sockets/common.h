#pragma once

#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include<errno.h>
#include<assert.h>
#include<unistd.h>
#include<wait.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<string.h>
#include<pthread.h>
#include<netdb.h>
using namespace std;
#pragma pack(1)
struct req
{
	char ver;
	char method_n;
};
struct rep
{
	char ver;
	char method;
};
struct mesq
{
	char ver;
	char cmd;
	char rsv;
	char atyp;
};
struct mesp
{
	char ver;
	char rep;
	char rsv;
	char atyp; 
	in_addr_t ip;	
	short port;
};
struct fd_thread
{
	int in;
	int out;
	pthread_t pid;
	fd_thread(int fin,int fout,pthread_t fid)
	:in(fin)
	,out(fout)
	,pid(fid)
	{}
};
void* transfer(void* arg);
void enx(void* data,int len);
