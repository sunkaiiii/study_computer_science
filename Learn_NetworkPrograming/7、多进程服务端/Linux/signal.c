#include<stdio.h>
#include<unistd.h>
#include<signal.h>

void timeout(int sig)
{
  if(sig==SIGALRM)
    puts("Time out");
  alarm(2);
}

void keycontrol(int sig)
{
  if(sig==SIGINT)
    puts("CTRL+C pressed");
}

int main(int argc,char *argv)
{
  int i;
  signal(SIGALRM,timeout);
  signal(SIGINT,keycontrol);

  alarm(2);
  for(i=0;i<3;++i)
  {
    puts("wait...");
    sleep(100); //乍看之下程序可能要运行300秒，但是实际上，当出发信号的时候，就会唤醒由于sleep
                //阻塞的进程，大概只需要10秒就可以执行完，如果按下ctrl+c，可能会更快
  }
  return 0;
}
