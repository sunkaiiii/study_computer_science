/*
使用signal系统调用捕捉信号量
此程序选择忽略这个信号
*/
#include<stdio.h>
#include<signal.h>

int main()
{
  signal(SIGINT,SIG_IGN); //当获取到SIGINT信号量的时候，执行f
  for(int i=0;i<5;i++)
  {
    printf("hello\n");
    sleep(1);
  }
}
