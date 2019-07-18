/*
popen命令的一个实现
*/

#include<stdio.h>
#include<signal.h>

#define READ 0
#define WRITE 1

FILE *popen(const char * command,const char * mode)
{
  int pfp[2],pid; //管道和fork
  FILE *fdopen(),*fp; //fdopen将会返回一个fd流
  int parent_end,child_end;

  if(*mode=='r') //确定目标
  {
    parent_end=READ;
    child_end=WRITE;
  }
  else if(*mode=='w')
  {
    parent_end=WRITE;
    child_end=READ;
  }
  else
    return NULL;
  if(pipe(pfp)==-1) //建立管道
    return NULL;
  if((pid=fork())==-1)
  {
    close(pfp[0]); //失败的时候关闭管道
    close(pfp[1]);
    return NULL;
  }
  if(pid>0) //父进程的操作：关闭一个管道，然后fdopen另外一个
  {
    if(close(pfp[child_end])==-1)
      return NULL;
    return fdopen(pfp[parent_end],mode);
  }

  /*子进程的操作*/
  /*重定向stdin和stdout然后exec cmd*/
  if(close(pfp[parent_end])==-1)
    exit(1);
  if(dup2(pfp[child_end],child_end)==-1)
    exit(1);
  if(close(pfp[child_end])==-1)
    exit(1);
  execl("/bin/sh","sh","-c",command,NULL);
  exit(1);
}
int main(int ac,char **av)
{
  if(ac!=2)
    perror("error");
  popen(av[1],'r');
}
