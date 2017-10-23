/*
将fork和管道结合起来
*/
#include<stdio.h>

#define CHILD_MESS "I want a cookie\n"
#define PAR_MESS "test..\n"
#define oops(m,x) {perror(m);exit(x);}

main()
{
  int pipefd[2];
  int len;
  char buf[BUFSIZ];
  int read_len;

  if(pipe(pipefd)==-1)
    oops("connot get a pipe",1);
  switch(fork())
  {
    case -1:
      oops("cannot fork",2);
    /*子进程每5秒写入一次管道*/
    case 0:
      len=strlen(CHILD_MESS);
      while(1)
      {
        if(write(pipefd[1],CHILD_MESS,len)!=len)
          oops("write",3);
        sleep(5);
      }
    /*父进程从管道里读取，也向管道写入*/
    default:
      len=strlen(PAR_MESS);
      while(1)
      {
        if(write(pipefd[1],PAR_MESS,len)!=len)
          oops("write",4);
        sleep(1);
        read_len=read(pipefd[0],buf,BUFSIZ);
        if(read_len<=0)
          break;
        write(1,buf,read_len);
      }
  }
}
