#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<signal.h>
#include<sys/wait.h>
#include<arpa/inet.h>
#include<sys/socket.h>

//一个保存消息的回声客户端
//使用管道进行进程间的通信，将客户端传来的文本存到文件中

#define BUF_SIZE 30
void error_handling(char *message);
void read_childproc(int sig);

int main(int argc,char *argv[])
{
  if(argc!=2)
  {
    printf("Usage :%s <port>\n",argv[0]);
    exit(1);
  }
  int serv_sock,clnt_sock;
  struct sockaddr_in serv_adr,clnt_adr;
  int fds[2]; //因为只是需要一个单向通信，所以只用一个管道
  pid_t pid;

  struct sigaction act;
  socklen_t adr_sz;
  int str_len,state;
  char buf[BUF_SIZE];
  act.sa_handler=read_childproc;
  sigemptyset(&act.sa_mask);
  act.sa_flags=0;
  state=sigaction(SIGCHLD,&act,0);

  serv_sock=socket(PF_INET,SOCK_STREAM,0);
  memset(&serv_adr,0,sizeof(serv_adr));
  serv_adr.sin_family=AF_INET;
  serv_adr.sin_addr.s_addr=htonl(INADDR_ANY);
  serv_adr.sin_port=htons(atoi(argv[1]));
  if(bind(serv_sock,(struct sockaddr*)&serv_adr,sizeof(serv_adr))==-1)
    error_handling("bind() error");
  if(listen(serv_sock,5)==-1)
    error_handling("listen() error");

  pipe(fds);
  pid=fork();
  if(pid==0)
  {
    FILE *fp=fopen("echomsg.txt","wt");
    char msgbuf[BUF_SIZE];
    int i,len;
    for(int i=0;i<10;i++)
    {
      len=read(fds[0],msgbuf,BUF_SIZE);
      fwrite((void*)msgbuf,1,len,fp);
    }
    fclose(fp);
    return 0;
  }
  else
  {
    while(1)
    {
      adr_sz=sizeof(clnt_adr);
      clnt_sock=accept(serv_sock,(struct sockaddr*)&clnt_adr,&adr_sz);
      if(clnt_sock==-1)
        continue;
      else
        puts("new client connected...\n");
      pid=fork();
      if(pid==-1)
      {
        close(clnt_sock);
        continue;
      }
      if(pid==0)
      {
        close(serv_sock);
        while((str_len=read(clnt_sock,buf,BUF_SIZE))!=0)
        {
          write(clnt_sock,buf,str_len);
          write(fds[1],buf,str_len);
        }
        close(clnt_sock);
        puts("client disconencted...\n");
        return 0;
      }
      else{
        close(clnt_sock);
      }
    }
  }
  close(serv_sock);
  return 0;
}

void read_childproc(int sig)
{
  pid_t pid;
  int status;
  pid=waitpid(-1,&status,WNOHANG); //防止僵尸进程
  printf("removed pro id :%d\n",pid);
}

void error_handling(char *message)
{
  fputs(message,stderr);
  fputc('\n',stderr);
  exit(1);
}
