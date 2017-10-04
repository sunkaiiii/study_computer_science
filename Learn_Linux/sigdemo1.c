/*
使用signal系统调用捕捉信号量
*/
#include<stdio.h>
#include<signal.h>

int main()
{
  void f(int);
  int i;
  signal(SIGINT,f); //当获取到SIGINT信号量的时候，执行f
  for(int i=0;i<5;i++)
  {
    printf("hello\n");
    sleep(1);
  }
}

void f(int signum)
{
  printf("OUCH!\n");
}
