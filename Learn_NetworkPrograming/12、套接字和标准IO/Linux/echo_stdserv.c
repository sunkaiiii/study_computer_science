#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>

//基于套接字的标准I/O函数使用
#define BUF_SIZE 1024

void error_handling(char *message);
int main(int argc,char *argv[])
{
  int serv_sock,clnt_sock;
  char message[BUF_SIZE];
  int str_len,i;

  FILE *readfp;
  FILE *writefp;

  struct sockaddr_in ser_adr,clnt_adr;
  socklen_t clnt_adr_sz;
  if(argc!=2){
    printf("Usage :%s <port>\n",argv[0]);
    exit(1);
  }

  serv_sock=socket(PF_INET,SOCK_STREAM,0);
  if(serv_sock==-1)
    error_handling("socket() error");

  memset(&ser_adr,0,sizeof(ser_adr));
  ser_adr.sin_family=AF_INET;
  ser_adr.sin_addr.s_addr=htonl(INADDR_ANY);
  ser_adr.sin_port=htons(atoi(argv[1]));
  if(bind(serv_sock,(struct sockaddr*)&ser_adr,sizeof(ser_adr))==-1)
    error_handling("bind() error");
  if(listen(serv_sock,5)==-1)
    error_handling("listen() error");

  clnt_adr_sz=sizeof(clnt_adr);
  for(int i=0;i<5;i++)
  {
    clnt_sock=accept(serv_sock,(struct sockaddr*)&clnt_adr,&clnt_adr_sz);
    if(clnt_sock==-1)
     error_handling("acept() errror");
   else
     printf("Connect client %d\n",i+1);
    //将套接字转换为文件描述符
    readfp=fdopen(clnt_sock,"r");
    writefp=fdopen(clnt_sock,"w");
    while(!feof(readfp))
    {
      fgets(message,BUF_SIZE,readfp);
      fputs(message,writefp);
      fflush(writefp);
    }
    fclose(readfp);
    fclose(writefp);
  }
  close(clnt_sock);
  return 0;
}
void error_handling(char *message)
{
  fputs(message,stderr);
  fputc('\n',stderr);
  exit(1);
}
