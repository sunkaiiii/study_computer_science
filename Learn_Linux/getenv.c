#include<stdlib.h>
int main(int argc,char *argv[])
{
  if(argc!=2)
    exit(1);
  char *cp=getenv(argv[1]);
  if(cp!=NULL)
    printf("%s:%s\n",argv[1],cp);
}
