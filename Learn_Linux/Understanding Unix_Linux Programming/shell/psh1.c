/*
编写shell的第一个版本程序
输入要执行的命令和参数
通过execvp执行命令
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
  execvp(arglist[0],arglist);
  perror("execvp failed");
  exit(1);
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
