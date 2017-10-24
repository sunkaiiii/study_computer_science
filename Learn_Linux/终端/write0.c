/*
write0.c
向其他终端发送信息
参数需要终端的文件名(ttyname)
*/
#include<stdio.h>
#include<fcntl.h>
int main(int ac,char*av[])
{
  int fd;
  char buf[BUFSIZ];
  /*检查参数*/
  if(ac!=2)
  {
    fprintf(stderr, "usage:write0 ttyname\n");
    exit(1);
  }
  /*打开终端设备文件*/
  fd=open(av[1],O_WRONLY);
  if(fd==-1)
  {
    perror(av[1]);
    exit(1);
  }
  /*循环直到输入EOF*/
  while(fgets(buf,BUFSIZ,stdin)!=NULL)
  {
    if(write(fd,buf,strlen(buf))==-1)
    {
      break;
    }
  }
  close(fd);
}