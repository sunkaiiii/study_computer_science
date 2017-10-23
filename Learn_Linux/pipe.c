/*
将io重定向，pipe，fork结合在一起，玩车搞一个通用的程序pipe
*/
#include<stdio.h>
#include<unistd.h>

#define oops(m,x) {perror(m);exit(x);}

main(int ac,char**av)
{
  int thepipe[2],newfd,pid;
  if(ac!=3) //判断参数
  {
    fprintf(stderr,"usage:pipe cmd1 cmd2\n");
    exit(1);
  }
  if(pipe(thepipe)==-1)
    oops("Cannot get a pipe",1);

  //创建完管道之后，创建子进程
  if((pid=fork())==-1)
    oops("Cannot fork",2);

  /*
  *现在，创建好了进程，3 父进程将会从管道读取
  */
  printf("pid:%d\n",pid);
  if(pid>0)
  {

    close(thepipe[1]); //父进程不需要写入
    if(dup2(thepipe[0],0)==-1) //将管道读取端重定向到标准输入，这样，从管道中读取的内容将会被标准输入获取
      oops("could not redirect stdin",3);
    close(thepipe[0]); //管道读取端已经定向到标准输入，原来的文件描述符可以关闭了
    execlp(av[2],av[2],NULL);
    oops(av[2],4);
  }

  /*
  *子进程将会执行av[1]，并向管道中写入数据
  */
  close(thepipe[0]); //子进程不需要从管道中读取数据
  if(dup2(thepipe[1],1)==-1) //将管道输入端与标准输出绑定,这样执行程序输出的内容将写入管道
    oops("could not redirect stdout",4);
  close(thepipe[1]); //关闭原来的文件描述符
  execlp(av[1],av[1],NULL);
  oops(av[1],5);
}
