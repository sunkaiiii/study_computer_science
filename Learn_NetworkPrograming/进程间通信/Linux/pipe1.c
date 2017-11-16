#include<stdio.h>
#include<unistd.h>
#define BUF_SZIE 30
//简单的管道使用

int main(int argc,char *argv[])
{
  int fds[2];
  char str[]="who are you";
  char buf[BUF_SZIE];
  pid_t pid;

  pipe(&fds);

  pid=fork();
  if(pid==0) //子进程
  {
    write(fds[1],str,sizeof(str)); //子进程向管道入口写入
  }
  else //父进程
  {
    read(fds[0],buf,BUF_SZIE); //父进程从管道出口读取
    puts(buf);
  }
  return 0;
}
