/*
close then open 方式
展示io重定向通过替换文件描述符
*/
#include<stdio.h>
#include<fcntl.h>

main()
{
  int fd;
  char line[100];

  /*读取和打印3行*/
  fgets(line,100,stdin);
  printf("%s",line);
  fgets(line,100,stdin);
  printf("%s",line);
  fgets(line,100,stdin);
  printf("%s",line);

  /*重定向输入*/
  close(0); //如果之后不打开文件，标准输入将没有输入源
  fd=open("/etc/passwd",O_RDONLY);
  if(fd!=0)
  {
    fprintf(stderr,"Could not open data as fd 0 \n");
    exit(1);
  }

  /*读取和打印3行*/
  fgets(line,100,stdin);
  printf("%s",line);
  fgets(line,100,stdin);
  printf("%s",line);
  fgets(line,100,stdin);
  printf("%s",line);
}
