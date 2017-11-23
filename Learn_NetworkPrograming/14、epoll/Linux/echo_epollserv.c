#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<sys/time.h>
#include<sys/epoll.h>

#define BUF_SIZE 100
#define EPOLL_SIZE 50
//基于epoll的回声服务器端
void error_handling(char *message);

int main(int argc,char *argv[])
{
  if(argc!=2)
  {
    printf("Usage :%s <port>\n",argv[0]);
    exit(1);
  }
  int serv_sock,clnt_sock;
  struct sockaddr_in serv_adr,clnt_adr;

  socklen_t adr_sz;
  int fd_max,str_len,fd_num,i;
  char buf[BUF_SIZE];

  //一些epoll相关的变量
  struct epoll_event *ep_events;
  struct epoll_event event;
  int epfd,event_cnt;

  serv_sock=socket(PF_INET,SOCK_STREAM,0);
  memset(&serv_adr,0,sizeof(serv_adr));
  serv_adr.sin_family=AF_INET;
  serv_adr.sin_addr.s_addr=htonl(INADDR_ANY);
  serv_adr.sin_port=htons(atoi(argv[1]));
  if(bind(serv_sock,(struct sockaddr*)&serv_adr,sizeof(serv_adr))==-1)
    error_handling("bind() error");
  if(listen(serv_sock,5)==-1)
    error_handling("listen() error");


  //设置EPOLL
  epfd=epoll_create(EPOLL_SIZE);
  ep_events=malloc(sizeof(struct epoll_event)*EPOLL_SIZE);
  event.events=EPOLLIN; //监控需要读取数据的情况
  event.data.fd=serv_sock; //要监控的套接字
  epoll_ctl(epfd,EPOLL_CTL_ADD,serv_sock,&event); //添加套接字
  while(1)
  {

    event_cnt=epoll_wait(epfd,ep_events,EPOLL_SIZE,-1);

    if(event_cnt==-1)
    {
      puts("epoll_wait() error");
      break;
    }

    for(int i=0;i<event_cnt;++i) //遍历那些发生变化的套接字
    {
      if(ep_events[i].data.fd==serv_sock) //连接请求
      {
        adr_sz=sizeof(clnt_adr);
        clnt_sock=accept(serv_sock,(struct sockaddr*)&clnt_adr,&adr_sz);
        event.events=EPOLLIN;
        event.data.fd=clnt_sock;
        epoll_ctl(epfd,EPOLL_CTL_ADD,clnt_sock,&event);
        printf("connected client : %d\n",clnt_sock);
      }
      else
      {
        str_len=read(ep_events[i].data.fd,buf,BUF_SIZE);
        if(str_len==0) //断开请求
        {
          epoll_ctl(epfd,EPOLL_CTL_DEL,ep_events[i].data.fd,NULL); //删除epoll中对应的信息
          close(ep_events[i].data.fd);
          printf("closed client:%d\n",ep_events[i].data.fd);
        }
        else
        {
          write(ep_events[i].data.fd,buf,str_len); //返回数据
        }
      }
    }
  }
  close(epfd);
  close(serv_sock);
  return 0;
}

void error_handling(char *message)
{
  fputs(message,stderr);
  fputc('\n',stderr);
  exit(1);
}
