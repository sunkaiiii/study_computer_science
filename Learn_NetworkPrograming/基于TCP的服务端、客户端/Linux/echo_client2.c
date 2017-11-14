
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>

//echo客户端的第二个实现
//解决可能收到多个字符串或者没收到完整字符串就输出的情况
#define BUF_SIZE 1024

void error_handling(char *message);
int main(int argc,char *argv[])
{
  if(argc!=3)
  {
    printf("Usage:%s <ip> <port> \n",argv[0]);
    exit(1);
  }
  int sock;
  char message[BUF_SIZE];
  int str_len,recv_len,recv_cnt; //设置一个接收计数
  struct sockaddr_in serv_adr;

  sock=socket(PF_INET,SOCK_STREAM,0);
  if(sock==-1)
    error_handling("socket() error");
  memset(&serv_adr,0,sizeof(serv_adr));
  serv_adr.sin_family=AF_INET;
  serv_adr.sin_addr.s_addr=inet_addr(argv[1]);
  serv_adr.sin_port=htons(atoi(argv[2]));
  if(connect(sock,(struct sockaddr*)&serv_adr,sizeof(serv_adr))==-1)
    error_handling("connect() error");
  else
    puts("Connect...............");
  while(1)
  {
    fputs("Input Message(Q to quit):",stdout);
    fgets(message,BUF_SIZE,stdin);
    if(!strcmp(message,"q\n")||!strcmp(message,"Q\n"))
      break;
    str_len=write(sock,message,strlen(message));
    if(str_len<0)
      error_handling("write() error");
    recv_len=0;
    while(recv_len<str_len)
    {
      recv_cnt=read(sock,&message[recv_len],BUF_SIZE-1);
      if(recv_cnt==-1)
        error_handling("read() error");
      recv_len+=recv_cnt;
    }
    message[str_len]='\0';
    printf("Message from server: %s\n",message);
  }
  close(sock);
  return 0;
}

void error_handling(char *message)
{
  fputs(message,stderr);
  fputc('\n',stderr);
  exit(1);
}
