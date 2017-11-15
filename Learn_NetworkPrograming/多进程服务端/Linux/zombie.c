#include<stdio.h>
#include<unistd.h>

//一个展示产生僵尸进程的程序

int main(int argc,char* argv[])
{
  pid_t pid=fork();
  if(pid==0) //子进程
  {
    puts("Hi,I am a child");
  }
  else
  {
    printf("Child Pid is %d\n",pid);
    sleep(30);
  }
  if(pid==0)
    puts("End child process");
  else
    puts("End parent process");

  return 0;
}
