#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
void ErrorHandling(char *message);
#define BUF_SIZE 30
#define TRUE 1
#define FALSE 0
int main(int argc,char* argv[])
{
  if(argc!=2)
  {
    printf("Usage %s <port> \n",argv[0]);
    exit(1);
  }
  int serv_sock,clnt_sock;
  char message[BUF_SIZE];
  int option,str_len;
  socklen_t optlen,clnt_adr_sz;
  struct sockaddr_in serv_adr,clnt_adr;
  serv_sock=socket(PF_INET,SOCK_STREAM,0);
  if(serv_sock==-1)
    ErrorHandling("socket() error");
  //设置地址再分配（SO_REUSEADDR)为真，使之可以再分配处于timewait下的套接字和端口
  //则样可以在服务端强制重启之后立马重新bind之前用过的端口
  optlen=sizeof(option);
  option=TRUE;
  setsockopt(serv_sock,SOL_SOCKET,SO_REUSEADDR,(void*)&option,optlen);
  memset(&serv_adr,0,sizeof(serv_adr));
  serv_adr.sin_family=AF_INET;
  serv_adr.sin_addr.s_addr=htonl(INADDR_ANY);
  serv_adr.sin_port=htons(atoi(argv[1]));
  if(bind(serv_sock,(struct sockaddr*)&serv_adr,sizeof(serv_adr))==-1)
    ErrorHandling("bind() error");
  if(listen(serv_sock,5)==-1)
    ErrorHandling("listen() error");

  clnt_adr_sz=sizeof(clnt_adr);
  while(1)
  {
    clnt_sock=accept(serv_sock,(struct sockaddr*)&clnt_adr,&clnt_adr_sz);
    if(clnt_sock==-1)
      ErrorHandling("accept() error");
    while((str_len=read(clnt_sock,message,BUF_SIZE))!=0)
    {
      write(clnt_sock,message,str_len);
      write(1,message,str_len);
    }
    close(clnt_sock);
  }
  close(serv_sock);
}

void ErrorHandling(char *message)
{
	fputs(message, stderr);
	fputc('\n',stderr);
	exit(1);
}
