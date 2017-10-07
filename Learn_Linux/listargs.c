/*
打印在终端中的参数，然后打印一个stderr
*/
#include<stdio.h>
int main(int ac,char *av[])
{
  int i;
  printf("Number of args:%d,Args are:\n",ac);
  for(i=0;i<ac;i++)
  {
    printf("args[%d] %s\n",i,av[i]);
  }
  fprintf(stderr,"This is message is sent to stderr.\n");
}
