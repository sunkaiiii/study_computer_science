/*
监控两个输入描述符
使用select系统调用
*/
#include<stdio.h>
#include<sys/time.h>
#include<sys/types.h>
#include<unistd.h>
#include<fcntl.h>

#define oops(m,x){perror(m);exit(x);}

main(int ac,char *av[])
{
  int fd1,fd2; //需要监控的两个文件描述符
  struct timeval timeout; //超时时间
  fd_set readfds; //监控输入
  int maxfd; //最大的同时监控的描述符数量
  int retval; //select调用的返回值

  if(ac!=4)
  {
    fprintf(stderr,"usage: %s file file timeout",*av);
    exit(1);
  }
  /**打开文件**/
  if((fd1=open(av[1],O_RDONLY))==-1)
    oops(av[1],2);
  if((fd2=open(av[2],O_RDONLY))==-1)
    oops(av[2],3);
  maxfd=1+(fd1>fd2?fd1:fd2);
  while(1)
  {
    /*创建需要监控的文件列表*/
    FD_ZERO(&readfds); //清空内容
    FD_SET(fd1,&readfds); //设置内容
    FD_SET(fd2,&readfds);

    /*设置超时值*/
    timeout.tv_sec=atoi(av[3]); //设施毫秒
    timeout.tv_usec=0; //不设置秒了

    /*等待输入*/
    retval=select(maxfd,&readfds,NULL,NULL,&timeout);
    if(retval==-1)
      oops("select",4);
    if(retval>0)
    {
      /*检查bit*/
      if(FD_ISSET(fd1,&readfds))
        showdata(av[1],fd1);
      if(FD_ISSET(fd2,&readfds))
        showdata(av[2],fd2);
    }
    else
    {
      printf("no input after %d seconds\n",atoi(av[3]));
    }
  }
}

showdata(char *fname,int fd)
{
  char buf[BUFSIZ];
  int n;

  printf("%s: ",fname,n);
  fflush(stdout);
  n=read(fd,buf,BUFSIZ);
  if(n==-1)
    oops("read",5);
  write(1,buf,n);
  write(1,"\n",1);
}
