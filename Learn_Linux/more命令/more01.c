/*more的第一个实现版本*/
/*读取然后打印24行，并等待用户输入命令*/
#include<stdio.h>
#define PAGELINE 24
#define LINELEN 512
void do_more(FILE *);
int see_more();
int main(int ac,char *av[])
{
  FILE *fp;
  if(ac==1)
  {
    do_more(stdin);
  }
  else
  {
    while(--ac)
    {
      if((fp=fopen(*++av,"r"))!=NULL)
      {
        do_more(fp);
        fclose(fp);
      }
      else
      {
        perror("file open filed ");
        exit(1);
      }
    }
  }
  return 0;
}
void do_more(FILE *fp)
{
  /*读取每一行，然后调用see_more等待进一步指示*/
  char line[LINELEN];
  int num_of_lines=0;
  int see_more(),reply;
  while(fgets(line,LINELEN,fp)) //读取文本并打印在屏幕上
  {
    if(num_of_lines==PAGELINE) //是否已经输出满了整个屏幕？
    {
      reply=see_more();
      if(reply==0)
        break;
      num_of_lines-=reply; //重置打印计数
    }
    if(fputs(line,stdout)==EOF)
      exit(1);
    num_of_lines++;
  }
}

int see_more()
{
  /*打印消息，等待用户输入，q代表退出，空格代表yes，回车代表一行*/
  int c;
  printf("\033[7m more?\033[m");
  while((c=getchar())!=EOF)
  {
    if(c=='q')
      return 0;
    if(c==' ')
      return PAGELINE;
    if(c=='\n')
      return 1;
  }
  return 0;
}
