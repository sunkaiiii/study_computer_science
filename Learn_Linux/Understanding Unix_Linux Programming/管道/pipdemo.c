/*
展示如何创建一个管道
展示了一个从键盘到进程，从进程到管道，再从管道到进程以及进程回到终端的数据传输流
*/

#include<stdio.h>
#include<unistd.h>

main()
{
  int len,i,apipe[2]; //两个文件描述符
  char buf[BUFSIZ];

  /*获取一个管道*/
  if(pipe(apipe)==-1)
  {
    perror("could not make pipe");
    exit(1);
  }

  printf("Got a pipe!it is file descriptors:{%d %d}\n",apipe[0],apipe[1]);

  /*
  *apipe[1]是写入端，apipe[0]是读取端
  */

  /*从标准输入中读取，写入管道，从管道中读取，输出*/
  while(fgets(buf,BUFSIZ,stdin))
  {
    len=strlen(buf);
    if(write(apipe[1],buf,len)!=len) //写入管道
    {
      perror("writing to pipe");
      break;
    }
    for(i=0;i<len;++i) //wipe
      buf[i]='X';
    len=read(apipe[0],buf,BUFSIZ); //从管道中读取
    if(len==-1)
    {
      perror("reading from pipe");
      break;
    }
    if(write(1,buf,len)!=len) //写入到描述符1,目前也就是终端
    {
      perror("writing to stdout");
      break;
    }
  }
}
