#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>

/*
调整了一部分代码，验证TCP套接字“传输的数据不存在数据边界”这个特性
记录了调用read的次数
*/

void errpr_handling(char *message);

int main(int argc,char* argv[])
{
  int sock;
  struct sockaddr_in serv_addr;
  char message[30];
  int str_len;
  int idx=0,read_len=0;

  if(argc!=3)
  {
    printf("Usage:%s <ip> <port>\n",argv[0]);
    exit(1);
  }
  sock=socket(PF_INET,SOCK_STREAM,0); //申请一个socket
  if(sock==-1)
    error_handling("socket() error");
  memset(&serv_addr,0,sizeof(serv_addr));
  serv_addr.sin_family=AF_INET;
  serv_addr.sin_addr.s_addr=inet_addr(argv[1]); //指定ip
  serv_addr.sin_port=htons(atoi(argv[2])); //指定端口

  if(connect(sock,(struct sockaddr*)&serv_addr,sizeof(serv_addr))==-1) //进行连接
    error_handling("connect() error");
  while(read_len=read(sock,&message[idx++],1)) //每次只读取1个字，记录读取次数
  {
    if(str_len==-1)
      error_handling("read() error");
      str_len+=read_len;
  }

  printf("Message from server:%s\n",message);
  printf("Function read call count:%d\n",str_len);
  close(sock);
  return 0;
}

void error_handling(char *message)
{
  fputs(message,stderr);
  fputc('\n',stderr);
  exit(1);
}
