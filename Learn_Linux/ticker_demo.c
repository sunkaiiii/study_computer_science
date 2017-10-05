/*
使用间隔计时器
*/
#include<stdio.h>
#include<sys/time.h>
#include<signal.h>

int main()
{
  void countdown(int);
  signal(SIGALRM,countdown);
  if(set_tickcer(500)==-1) //设置ticker的微秒数
    perror("set_tickcer");
  else
    while(1)
    {
      pause(); //主程序调用pause，其实在主程序这个里执行别的操作也是完全没问题的，计时器会发送SIGALRM并调用signum
    }
  return 0;
}

void countdown(int signum)
{
  static int num=10;
  printf("%d..",num--);
  fflush(stdout);
  if(num<0)
  {
    printf("DONE!\n");
    exit(0);
  }
}

int set_tickcer(int n_msecs)
{
  struct itimerval new_timeset;
  long n_sec,n_usecs;

  n_sec=n_msecs/1000; //int部分
  n_usecs=(n_msecs%1000)*1000L; //余数

  //设置初始间隔和重复间隔
  new_timeset.it_interval.tv_sec=n_sec; //重复时间
  new_timeset.it_interval.tv_usec=n_usecs; //小数（毫秒）

  new_timeset.it_value.tv_sec=n_sec; //初始时间
  new_timeset.it_value.tv_usec=n_usecs; //小数（毫秒）

  return setitimer(ITIMER_REAL,&new_timeset,NULL);
}
