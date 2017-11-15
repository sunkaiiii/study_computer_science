#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/socket.h>

void ErrorHandling(char *message);

int main(int argc,char *argv[])
{
  int tcp_sock,udp_sock;
  int sock_type;
  socklen_t optlen;
  int state;

  optlen=sizeof(sock_type);
  tcp_sock=socket(PF_INET,SOCK_STREAM,0);
  udp_sock=socket(PF_INET,SOCK_DGRAM,0);
  printf("SOCK_STREAM: %d\n",SOCK_STREAM);
  printf("SOCK_DGRAM:%d\n",SOCK_DGRAM);

  //sock,level(要查看的协议层),optname(要查看的选项名),optval(保存结果),optlen(传递缓冲大小)
  state=getsockopt(tcp_sock,SOL_SOCKET,SO_TYPE,(void*)&sock_type,&optlen);

  if(state)
    ErrorHandling("getsockopt() error");
  printf("Scoket type one :%d\n",sock_type);

  state=getsockopt(udp_sock,SOL_SOCKET,SO_TYPE,(void*)&sock_type,&optlen);
  if(state)
    ErrorHandling("getsockopt() error");
  printf("Scoket type one :%d\n",sock_type);
}

void ErrorHandling(char *message)
{
	fputs(message, stderr);
	fputc('\n',stderr);
	exit(1);
}
