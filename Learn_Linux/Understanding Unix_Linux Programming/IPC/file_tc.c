/*
基于文件的时间服务客户端代码
*/

#include<stdio.h>
#include<sys/file.h>
#include<fcntl.h>

#define oops(m,x){perror(m);exit(x);}
#define BUFLEN 10

main(int ac,char *av[])
{
  int fd,nread;
  char buf[BUFLEN];

  if(ac!=2)
  {
    fprintf(stderr,"usage:file_tc filename\n");
    exit(1);
  }
  if((fd=open(av[1],O_RDONLY))==-1) //打开时间文件
    oops(av[1],3);
  lock_operation(fd,F_RDLCK); //文件上锁
  while((nread=read(fd,buf,BUFLEN))>0) //读取时间数据
    write(1,buf,nread); //时间数据写入到输出流
  lock_operation(fd,F_UNLCK); //文件解锁
  close(fd);

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
