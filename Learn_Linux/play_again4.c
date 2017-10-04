/*
对用户显示问题，接受用户输入，如果是y返回1,是n返回0
在用户输入的时候关闭规范输入，使得在用户敲击的同时就可以得到输入的字符
并忽略非法键
同时使用非阻塞模式实现超时响应
并捕捉信号量，重置驱动程序然后返回no
*/
#include<stdio.h>
#include<termios.h>
#include<fcntl.h>
#include<string.h>
#include<signal.h>

#define QUESTION "Do you want anaother transaction"
#define TRIES 3
#define SLEEPTIME 2

BEEP(int tries)
{
  printf("\n%d",tries);
}

int get_reonse(char *,int);

int main()
{
  int response;
  void ctrl_c_handler(int);

  tty_mode(0);  //保存当前的设备驱动状态
  set_cro_noecho_mode();
  set_nodelay_mode();
  signal(SIGINT,ctrl_c_handler);
  signal(SIGQUIT,SIG_IGN);
  response=get_reonse(QUESTION,TRIES); //获取用户反馈
  tty_mode(1);
  return response;
}

int get_reonse(char *question,int maxtries)
{
  printf("%s (y/n)?",question);
  int input;
  fflush(stdout);
  while(1)
  {
    sleep(SLEEPTIME);
    input=get_ok_char();
    if(input=='y'||input=='Y')
      return 0;
    if(input=='n'||input=='N')
      return 1;
    if(maxtries--==0)
      return 2;
    BEEP(maxtries);
  }
}
/*
*跳过非法字符
*/
get_ok_char()
{
  int c;
  while((c=getchar())!=EOF&&strchr("yYnN",c)==NULL)
  ;
  return c;
}

set_cro_noecho_mode()
{
  /*设置终端驱动,并设置不回显*/
  struct termios ttystate;
  tcgetattr(0,&ttystate);
  ttystate.c_lflag&=~ICANON; //无缓冲
  ttystate.c_lflag&=~ECHO;
  ttystate.c_cc[VMIN]=1; //每次读取1个字符
  tcsetattr(0,TCSANOW,&ttystate); //写回终端驱动
}
set_nodelay_mode()
{
  int termflags;
  termflags=fcntl(0,F_GETFL);
  termflags|=O_NDELAY;
  fcntl(0,F_SETFL,termflags);
}

//how==0写入当前的mode，how==1的时候恢复mode
tty_mode(int how)
{
  static struct termios orignal_mode;
  static int original_flags;
  static int stored=0;
  if(how==0)
  {
    tcgetattr(0,&orignal_mode);
    original_flags=fcntl(0,F_GETFL);
    stored=1;
  }
  else if(stored)
  {
    tcsetattr(0,TCSANOW,&orignal_mode);
    fcntl(0,F_SETFL,original_flags);
  }
}
void ctrl_c_handler(int signal)
{
  //当从键盘输入ctrl+c的时候，重置ttymode
  tty_mode(1);
  exit(1);
}
