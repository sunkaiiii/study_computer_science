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
        perror("file open filed\n");
        exit(1);
      }
    }
  }
}
