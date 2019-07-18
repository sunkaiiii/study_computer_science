/*
使用ECHO与当前的设备状态bit相与，获得当前的终端回显状态
*/
#include<stdio.h>
#include<termios.h>

int main()
{
  struct termios info;
  int rv;
  rv=tcgetattr(0,&info);/*从驱动中读取值*/
  if(rv==-1)
  {
    perror("tcgetattr");
    exit(1);
  }
  if(info.c_lflag&ECHO)
    printf("echo is on,since its bit is 1\n");
  else
    printf("echo is off,since its bit is 0\n");
}
