/*
对用户显示问题，接受用户输入，如果是y返回1,是n返回0
在用户输入的时候关闭规范输入，使得在用户敲击的同时就可以得到输入的字符
并忽略非法键
同时使用非阻塞模式实现超时响应
play_again3.c有两个问题
1、在阻塞睡眠期间，用户的输入将不能得到反馈
2、在运行期间使用ctrl+c，程序无法回退回运行前的终端驱动设置
*/
#include<stdio.h>
#include<termios.h>
#include<fcntl.h>
#include<string.h>

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
  tty_mode(0);
  set_cro_noecho_mode();
  set_nodelay_mode();
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
  if(how==0)
  {
    tcgetattr(0,&orignal_mode);
    original_flags=fcntl(0,F_GETFL);
  }
  else
  {
    tcsetattr(0,TCSANOW,&orignal_mode);
    fcntl(0,F_SETFL,original_flags);
  }
}
