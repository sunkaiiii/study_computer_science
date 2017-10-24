/*
编写shell的第二个版本程序
输入要执行的命令和参数
使用fork创建子进程，并执行execvp调用程序
*/
#include<stdio.h>
#include<signal.h>
#include<string.h>
#include<stdlib.h>
#include<memory.h>

#define MAXARGS 20
#define ARGLEN 100

int main()
{
  char *arglist[MAXARGS+1];
  int numargs;
  char argbuf[ARGLEN];
  char *makestring();
  numargs=0;
  while(numargs<MAXARGS)
  {
    printf("Arg[%d]?",numargs);
    if(fgets(argbuf,ARGLEN,stdin)&&*argbuf!='\n')
    {
      arglist[numargs++]=makestring(argbuf);
    }
    else
    {
      if(numargs>0) //是否有命令
      {
        arglist[numargs]=NULL; //参数尾部置为0
        execute(arglist);
        numargs=0;
      }
    }
  }
  return 0;
}

int  execute(char *arglist[])
{
  /*使用fork和execvp，父进程等待子进程退出*/
  int pid,exitstatis;
  pid=fork();
  switch (pid) {
    case -1:
      perror("fork failed");
      exit(1);
    case 0:
      execvp(arglist[0],arglist); //子进程执行execvp
      perror("execvp failed");
      exit(1);
    default:
      signal(SIGINT,SIG_IGN); //父进程屏蔽ctrl+C,防止在子进程运行过程中按下ctrl+C后psh2被中止
      while(wait(&exitstatis)!=pid);
      printf("child exited with status %d,%d\n",exitstatis>>8,exitstatis&0337);
      signal(SIGINT,SIG_DFL); //子进程结束，父进程恢复ctrl+C的默认操作

  }
}

char *makestring(char *buf)
{
  char *cp;
  buf[strlen(buf)-1]='\0'; //去掉末尾的换行符
  cp=malloc(strlen(buf)+1);
  if(cp==NULL)
  {
    fprintf(stderr,"no memory\n");
    exit(1);
  }
  strcpy(cp,buf);
  return cp;
}
