/*
对用户显示问题，接受用户输入，如果是y返回1,是n返回0
在用户输入的时候关闭规范输入，使得在用户敲击的同时就可以得到输入的字符
*/
#include<stdio.h>
#include<termios.h>

#define QUESTION "Do you want anaother transaction"

int get_reonse(char *);

int main()
{
  int response;
  tty_mode(0);
  set_crmode();
  response=get_reonse(QUESTION); //获取用户反馈
  tty_mode(1);
  return response;
}

int get_reonse(char *question)
{
  printf("%s (y/n)?",question);
  int input;
  while(1)
  {
    switch(input=getchar())
    {
      case 'y':
      case 'Y':
        return 0;
      case 'n':
      case 'N':
      case EOF:
        return 1;
      default:
        printf("\ncannot understand %c ",input);
        printf("Please type y or no \n");
    }
  }
}

set_crmode()
{
  /*设置终端驱动*/
  struct termios ttystate;
  tcgetattr(0,&ttystate);
  ttystate.c_lflag&=~ICANON; //无缓冲
  ttystate.c_cc[VMIN]=1; //每次读取1个字符
  tcsetattr(0,TCSANOW,&ttystate); //写回终端驱动
}

//how==0写入当前的mode，how==1的时候恢复mode
tty_mode(int how)
{
  static struct termios orignal_mode;
  if(how==0)
    tcgetattr(0,&orignal_mode);
  else
    return tcsetattr(0,TCSANOW,&orignal_mode);
}
