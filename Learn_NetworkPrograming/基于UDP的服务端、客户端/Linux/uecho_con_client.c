#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#define BUF_SIZE 30
void error_handling(char *message);

//创建一个已连接的UDP套接字
int main(int argc,char *argv[])
{
  int sock;
  char message[BUF_SIZE];
  struct sockaddr_in serv_adr,from_adr;
  int str_len;
  socklen_t adr_sz;

  if(argc!=3)
  {
    printf("Usage :%s <port>\n",argv[0]);
    exit(1);
  }
  sock=socket(PF_INET,SOCK_DGRAM,0);
  if(sock==-1)
    error_handling("socket() error");
  memset(&serv_adr,0,sizeof(serv_adr));
  serv_adr.sin_family=AF_INET;
  serv_adr.sin_addr.s_addr=inet_addr(argv[1]);
  serv_adr.sin_port=htons(atoi(argv[2]));

  connect(sock,(struct sockaddr*)&serv_adr,sizeof(serv_adr));

  while(1)
  {
    fputs("Insert Message(q to quit):",stdout);
    fgets(message,sizeof(message),stdin);
    if(!strcmp(message,"q\n")||!strcmp(message,"Q\n"))
    {
      break;
    }
    write(sock,message,strlen(message)); //建立连接的UDP可以使用write来发送数据
    str_len=read(sock,message,BUF_SIZE-1);
    message[str_len]='\0';
    printf("Message from server:%s\n",message);
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
