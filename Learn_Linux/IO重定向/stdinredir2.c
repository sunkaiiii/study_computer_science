/*
open close dup close 方式
使用dup建立指向已经存在的文件描述符的第二个连接
*/
#include<stdio.h>
#include<fcntl.h>


main()
{
  int fd;
  int newfd;
  char line[100];

  /*读取和打印3行*/
  fgets(line,100,stdin);
  printf("%s",line);
  fgets(line,100,stdin);
  printf("%s",line);
  fgets(line,100,stdin);
  printf("%s",line);
  /*重定向输入*/

  fd=open("/etc/passwd",O_RDONLY);
  printf("描述符fd:%d\n",fd);
  #ifdef CLOSE_DUP
  close(0);
  /*dup的作用是将文件描述符fd做了复制，并且复制后使用最低可用文件描述符，也就是0 */
  newfd=dup(fd); //copy fd到0
  #else
  /*dup2系统调用是close(0)+dup(fd)的结合*/
  /*dup2(orig,new) 将old描述符复制到新的描述符new，在此之前会将new原来的描述符关闭*/
  newfd=dup2(fd,0);  //关闭0，dup fd到0
  #endif
  if(newfd!=0)
  {
    fprintf(stderr,"Could not duplicate fd to 0 \n");
    exit(1);
  }
  close(fd);
  /*读取和打印3行*/
  fgets(line,100,stdin);
  printf("%s",line);
  fgets(line,100,stdin);
  printf("%s",line);
  fgets(line,100,stdin);
  printf("%s",line);
}
