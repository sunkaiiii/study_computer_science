#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/socket.h>
void ErrorHandling(char *message);

int main(int argc,char *argv[])
{
  int sock;
  int snd_buf=1024*3,rcv_buf=1024*3,state;
  socklen_t len;
  sock=socket(PF_INET,SOCK_STREAM,0);

  //sock,level(要修改的协议层),optname(要修改的协议名),optval(要修改的值),optlen(第四个参数的大小)
  state=setsockopt(sock,SOL_SOCKET,SO_RCVBUF,(void*)&rcv_buf,sizeof(rcv_buf));
  if(state)
    ErrorHandling("setsockopt() error");
  state=setsockopt(sock,SOL_SOCKET,SO_SNDBUF,(void*)&snd_buf,sizeof(snd_buf));
  if(state)
    ErrorHandling("setsockopt() error");
  len=sizeof(snd_buf);
  len=sizeof(snd_buf);
  state=getsockopt(sock,SOL_SOCKET,SO_SNDBUF,(void*)&snd_buf,&len);
  if(state)
    ErrorHandling("getsockopt() error");
  len=sizeof(rcv_buf);
  state=getsockopt(sock,SOL_SOCKET,SO_RCVBUF,(void*)&rcv_buf,&len);
  if(state)
    ErrorHandling("getsockopt() error");
  printf("Input buffer size: %d\n",rcv_buf);
  printf("Output buffer size %d\n",snd_buf);
}
void ErrorHandling(char *message)
{
	fputs(message, stderr);
	fputc('\n',stderr);
	exit(1);
}
