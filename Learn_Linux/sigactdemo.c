/*
测试如何使用sigaction()
效果：当处理ctrl+C的时候屏蔽ctrl+\
*/
#include<stdio.h>
#include<signal.h>
#define INPUTLEN 100

int main()
{
  struct sigaction newhandler; //新的处理设置
  sigset_t blocked; //设置要屏蔽的信号量
  void inthandler();
  char x[INPUTLEN];

  /*首先读取这两个成员*/
  newhandler.sa_handler=inthandler; //设置处理器
  newhandler.sa_flags=SA_RESETHAND|SA_RESTART; //设置options 设置SA_RESETHAND后，第一次执行玩ctrl+c会重置信号处理方法

  /*
  * SA_RESETHAND 当处理函数被调用时重置
  * SA_NODEFER 在处理信号的时候使用非阻塞模式，允许重复调用信号处理
  * SA_RESTART 当系统调用一些慢速的设备或者类似的系统调用，重新开始，而不是返回。
  * SA_SIGINFO 指明使用sa_sigaction的处理函数的值。如果这个位没有被设置，那么就使用sa_handler指向的处理函数的值。如果sa_sigaction被使用
  *传给处理函数的将不只是信号编号，还包括只想描述信号产生的原因和条件的结构体

  /*然后建立屏蔽的信号量名单*/
  sigemptyset(&blocked); //清除所有的bit
  sigaddset(&blocked,SIGQUIT); //添加SIGQUIT到屏蔽名单中
  newhandler.sa_mask=blocked;

  if(sigaction(SIGINT,&newhandler,NULL)==-1)
    perror("sigaction");
  else
    while(1)
    {
      fgets(x,INPUTLEN,stdin);
      printf("input: %s",x);
    }
}

void inthandler(int s)
{
  printf("Called with signal %d\n",s);
  sleep(s);
  printf("done handling signal %d\n",s);
}
