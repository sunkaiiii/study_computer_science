#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>

#define BUF_SIZE 1024
#define OPSZ 4
void error_handling(char *message);
int calculate(int opnum,int opnds[],char operator);
int main(int argc,char *argv[])
{
  if(argc!=2){
    printf("Usage :%s <port>\n",argv[0]);
    exit(1);
  }

  int serv_sock,clnt_sock;
  char opinfo[BUF_SIZE];
  struct sockaddr_in serv_addr,clnt_addr;
  int opnd_cnt,result,i;
  int recv_len,recv_cnt;

  if((serv_sock=socket(PF_INET,SOCK_STREAM,0))==-1)
    error_handling("socket() error");
  memset(&serv_addr,0,sizeof(serv_addr));
  serv_addr.sin_family=AF_INET;
  serv_addr.sin_addr.s_addr=htonl(INADDR_ANY);
  serv_addr.sin_port=htons(atoi(argv[1]));
  if(bind(serv_sock,(struct sockaddr*)&serv_addr,sizeof(serv_addr))==-1)
    error_handling("bind() error");
  if(listen(serv_sock,5)==-1)
    error_handling("listen error");
  socklen_t clnt_adr_sz;
  while(1)
  {
    opnd_cnt=0;
    clnt_adr_sz=sizeof(clnt_addr);
    if((clnt_sock=accept(serv_sock,(struct sockaddr*)&clnt_addr,&clnt_adr_sz))==-1)
      error_handling("accept() error");
    recv_len=0;
    read(clnt_sock,&opnd_cnt,1); //读取有多少个数
    printf("opnd_cnt:%d\n",opnd_cnt);
    while((opnd_cnt*OPSZ+1)>recv_len)
    {
      recv_cnt=read(clnt_sock,&opinfo[recv_len],BUF_SIZE-1);
      recv_len+=recv_cnt;
    }
    result=calculate(opnd_cnt,(int*)opinfo,opinfo[recv_len-1]);
    printf("result:%d\n",result);
    write(clnt_sock,(char*)&result,sizeof(result));
    close(clnt_sock);
  }
}
int calculate(int opnum,int opnds[],char op)
{
  int result=opnds[0],i;
  switch(op)
  {
    case '+':
      for(i=1;i<opnum;++i)
        result+=opnds[i];
      break;
    case '-':
      for(i=1;i<opnum;++i)
        result-=opnds[i];
      break;
    case '*':
      for(i=1;i<opnum;++i)
        result*=opnds[i];
      break;
  }
  return result;
}
void error_handling(char *message)
{
  fputs(message,stderr);
  fputc('\n',stderr);
  exit(1);
}
