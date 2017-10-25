/*
基于文件的时间服务器
演示fcntl的使用
*/
#include<stdio.h>
#include<sys/file.h>
#include<fcntl.h>
#include<time.h>
#include<string.h>
#include<stdlib.h>

#define oops(m,x){perror(m);exit(x);}

main(int ac,char *av[])
{
  int fd;
  time_t now;
  char *message;
  void lock_operation(int,int);
  if(ac!=2)
  {
    fprintf(stderr,"usage: file_ts filename\n");
    exit(1);
  }

  if((fd=open(av[1],O_CREAT|O_TRUNC|O_WRONLY,0644))==-1) //创建一个文件用来记录时间
    oops(av[1],2);

  while(1)
  {
    time(&now);
    message=ctime(&now); //获取当前的时间

    lock_operation(fd,F_WRLCK); //文件上锁

    if(lseek(fd,0L,SEEK_SET)==-1)
      oops("lseek",3);
    if(write(fd,message,strlen(message))==-1) //写入当前的时间
      oops("write",4);
    lock_operation(fd,F_UNLCK); //解锁
    sleep(1);
  }
}

void lock_operation(int fd,int op)
{
  struct flock lock;

  lock.l_whence=SEEK_SET;
  lock.l_start=lock.l_len=0;
  lock.l_pid=getpid();
  lock.l_type=op;

  if(fcntl(fd,F_SETLKW,&lock)==-1)
    oops("lock operation",6);
}
