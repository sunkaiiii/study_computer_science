/*
一个基于socket的时间日期服务器
*/
#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>
#include<time.h>
#include<strings.h>

#define PROTNUM 4091 /*我们的时间服务器的端口号*/
#define HOSTLEN 256
#define oops(msg){perror(msg);exit(1);}


int main(int ac,char *av[])
{
  struct sockaddr_in saddr; //建立我们的地址
  struct hostent *hp; //hour的一部分
  char hostname[HOSTLEN]; //地址
  int sock_id,sock_fd;
  FILE *sock_fp;  //把socket作为流
  char *ctime();  //转换秒为时间
  time_t thetime;

  /*第一步，向内核申请socket*/
  sock_id=socket(PF_INET,SOCK_STREAM,0); //获取一个socket
  if(sock_id==-1)
    oops("socket");

  /*第二步，绑定地址，端口*/
  bzero((void*)&saddr,sizeof(saddr)); //清理struct
  gethostname(hostname,HOSTLEN);
  hp=gethostbyname(hostname);
  bcopy((void*)hp->h_addr,(void*)&saddr.sin_addr,hp->h_length); //fill in host part
  saddr.sin_port=htons(PROTNUM); //fill socket port
  saddr.sin_family=AF_INET; //fill in addr family
  if(bind(sock_id,(struct sockaddr*)&saddr,sizeof(saddr))!=0)
    oops("bind");

  /*第三步，运行需来自Qsize=1的 socket通信*/
  if(listen(sock_id,1)!=0)
    oops("listen");

  /*循环等待接收*/
  while(1)
  {
    printf("start accept\n"); 
    sock_fd=accept(sock_id,NULL,NULL);
    printf("get a call\n");
    if(sock_fd==-1)
      oops("accept");
    sock_fp=fdopen(sock_fd,"w");
    if(sock_fp==NULL)
      oops("fdopen");
    thetime=time(NULL);
    fprintf(sock_fp,"The time here is ..");
    fprintf(sock_fp, "%s",ctime(&thetime) );
    fclose(sock_fp);
  }
}
