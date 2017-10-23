/*
展示如何重定向到文件
等同于在shell中输入
who>userlist
*/

#include<stdio.h>

main()
{
  int pid;
  int fd;
  printf("About to run who into a file\n");

  /*创建新的进程*/
  if((pid==fork())==-1)
  {
    perror("fork");
    exit(1);
  }
  //子进程的工作
  if(pid==0)
  {
    close(1); //关闭1 (stdout);
    fd=creat("userlist",0644); //打开新的文件，文件描述符1现在指向文件userlist 
    execlp("who","who",NULL); //执行execlp之后，who的代码回覆盖接下来的部分，但是文件描述符是保留的，于是who向文件描述符1写入，实际上就是写入文件
    perror("execlp");
    exit(1);
  }
  if(pid!=0)
  {
    wait(NULL);
    printf("DOne running who.results in userlist\n");
  }
}
