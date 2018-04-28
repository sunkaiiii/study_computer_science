#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<pthread.h>

#define BUF_SIZE 100
#define MAX_CLNT 256

//多线程并发服务器的实现

void error_handling(char *message);
void send_msg(char *msg,int len);
void *handle_clnt(void *arg);

int clnt_cnt=0;
int clnt_socks[MAX_CLNT];
pthread_mutex_t mutx;

int main(int argc,char *argv[])
{
    if(argc!=2)
    {
        printf("Usage :%s <port>\n",argv[0]);
        exit(1);
    }
    int serv_sock,clnt_sock;
    struct sockaddr_in serv_adr,clnt_adr;
    int clnt_adr_sz;
    pthread_t t_id;

    pthread_mutex_init(&mutx,NULL);
    serv_sock=socket(PF_INET,SOCK_STREAM,0);

    memset(&serv_adr,0,sizeof(serv_adr));
    serv_adr.sin_family=AF_INET;
    serv_adr.sin_addr.s_addr=htonl(INADDR_ANY);
    serv_adr.sin_port=htons(atoi(argv[1]));

    if(bind(serv_sock,(struct sockaddr*)&serv_adr,sizeof(serv_adr))==-1)
        error_handling("bind() error");

    if(listen(serv_sock,5)==-1)
        error_handling("listen() error");

    while(1)
    {
        clnt_adr_sz=sizeof(clnt_adr);
        clnt_sock=accept(serv_sock,(struct sockaddr*)&clnt_adr,&clnt_adr_sz);

        pthread_mutex_lock(&mutx);
        clnt_socks[clnt_cnt++]=clnt_sock;
        pthread_mutex_unlock(&mutx);

        //保存新创建的线程id的变量的地址值，传入null则以默认属性创建线程，相当于线程的main函数，参数
        pthread_create(&t_id,NULL,handle_clnt,(void*)&clnt_sock);
        pthread_detach(t_id); //调用detach不会像join一样使得当前进程阻塞，并且可以通过该函数引导销毁线程创建的内存空间
        printf("Connected client sock:%d IP:%s\n",clnt_sock,inet_ntoa(clnt_adr.sin_addr));
    }
    close(serv_sock);
    return 0;
}

void *handle_clnt(void *arg)
{
    int clnt_sock=*((int*)arg);
    int str_len=0,i;
    char msg[BUF_SIZE];

    while((str_len=read(clnt_sock,msg,BUF_SIZE))!=0)
        send_msg(msg,str_len);
    pthread_mutex_lock(&mutx); //移除断开连接的客户端
    //处理链接的数组
    for(i=0;i<clnt_cnt;++i)
    {
        if(clnt_sock==clnt_socks[i])
        {
            while(i++<clnt_sock-1)
                clnt_socks[i]=clnt_socks[i+1];
            break;
        }
    }
    clnt_cnt--;
    pthread_mutex_unlock(&mutx);
    printf("client %d disconnect\n",clnt_sock);
    close(clnt_sock);
    return NULL;
}

void send_msg(char *msg,int len)
{
    int i;
    pthread_mutex_lock(&mutx);
    for(i=0;i<clnt_cnt;i++)
        write(clnt_socks[i],msg,len); //向所有连接的客户端返回消息
    pthread_mutex_unlock(&mutx);
}

void error_handling(char *message)
{
    fputs(message,stderr);
    fputc('\n',stderr);
    exit(1);
}
