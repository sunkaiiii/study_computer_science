/*
用于展示sleep函数是如何工作的
*/
#include<stdio.h>
#include<signal.h>

int main()
{
  void wakeup(int);
  printf("about to sleep for 4 seconds\n");
  signal(SIGALRM,wakeup); //捕获SIGALRM信号量
  alarm(4);
  pause();
  printf("Morning so soon?\n");
  return 0;
}

void wakeup(int signum)
{
  #ifdef SHHH
    printf("Alarm recevied from kernel\n");
  #endif
}
