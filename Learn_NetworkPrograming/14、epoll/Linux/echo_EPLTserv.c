#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<sys/time.h>
#include<sys/epoll.h>

//了解epoll条件触发的特性
//相较于之前的epoll服务器主要有以下两点变化
//1、将调用read函数时使用的缓冲大小缩减为4字节
//2、插入验证epoll_wait函数调用次数的语句
#define BUF_SIZE 4
#define EPOLL_SIZE 4

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
    int str_len,i;
    char message[BUF_SIZE];

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

    event.events=EPOLLIN;
    event.data.fd=serv_sock;

    epfd=epoll_create(EPOLL_SIZE);
    ep_events=malloc(sizeof(struct epoll_event)*EPOLL_SIZE);

    epoll_ctl(epfd,EPOLL_CTL_ADD,serv_sock,&event);

    while(1)
    {
        event_cnt=epoll_wait(epfd,ep_events,EPOLL_SIZE,-1);
        if(event_cnt==-1)
        {
            puts("epoll_wait() error");
            break;
        }

        puts("return epoll_wait");
        for(i=0;i<event_cnt;i++)
        {
            if(ep_events[i].data.fd==serv_sock) //连接请求
            {
                adr_sz=sizeof(clnt_adr);
                clnt_sock=accept(serv_sock,(struct sockaddr*)&clnt_adr,&adr_sz);
                event.events=EPOLLIN;
                event.data.fd=clnt_sock;
                epoll_ctl(epfd,EPOLL_CTL_ADD,clnt_sock,&event);
                printf("connect client:%d\n",clnt_sock);
            }
            else //读取数据
            {
                str_len=read(ep_events[i].data.fd,message,BUF_SIZE);
                if(str_len==0) //断开请求
                {
                    epoll_ctl(epfd,EPOLL_CTL_DEL,ep_events[i].data.fd,NULL);
                    close(ep_events[i].data.fd);
                    printf("closed client:%d\n",ep_events[i].data.fd);
                }
                else
                {
                    write(ep_events[i].data.fd,message,str_len);
                }
            }
        }
    }
    close(serv_sock);
    close(epfd);
    return 0;
}

void error_handling(char *message)
{
    fputs(message,stderr);
    fputc('\n',stderr);
    exit(1);
}
