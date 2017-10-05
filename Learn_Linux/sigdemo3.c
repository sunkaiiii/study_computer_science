/*
测试多个信号量发生的时候系统的响应状态
问题1：新的信号量是否会影响前一个信号量？
问题2：当正在处理信号量1的时候又传递来一个信号量1时，如何处理？
问题3：当处理信号量1的时候又来了一个信号量2,如何处理？
问题4：当正在运行read()的时候，如何处理信号量？
*/
#include<stdio.h>
#include<signal.h>

#define INPUTLEN 100

int main(int ac,char *av[])
{
  void inthandler(int);
  void quithandler(int);
  char input[INPUTLEN];
  int nchars;

  signal(SIGINT,inthandler);
  signal(SIGQUIT,quithandler);

  do
  {
    printf("\nType a message\n");
    nchars=read(0,input,(INPUTLEN-1));
    if(nchars==-1)
      perror("read returned an error");
    else
    {
      input[nchars]='\0';
      printf("You typed: %s",input);
    }
  }while(strncmp(input,"quit",4)!=0);
}

void inthandler(int s)
{
  printf("Recevied signal %d ..waiting\n",s);
  sleep(2);
  printf("Leaving inthandler \n");
}

void quithandler(int s)
{
  printf("Recevied signal %d .. waiting\n",s);
  sleep(3);
  printf("Leaving quithandler\n");
}
