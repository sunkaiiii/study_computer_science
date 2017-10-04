/*
对用户显示问题，接受用户输入，如果是y返回1,是n返回0
需要用户按回车确认
*/
#include<stdio.h>
#include<termios.h>

#define QUESTION "Do you want anaother transaction"

int get_reonse(char *);

int main()
{
  int response;
  response=get_reonse(QUESTION); //获取用户反馈
  return response;
}

int get_reonse(char *question)
{
  printf("%s (y/n)?",question);
  while(1)
  {
    switch(getchar())
    {
      case 'y':
      case 'Y':
        return 0;
      case 'n':
      case 'N':
      case EOF:
        return 1;
    }
  }
}
