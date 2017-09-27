/*who1.c
实现了who命令的第一个程序版本，读取UTMP file，然后显示结果
*/
#include<stdio.h>
#include<utmp.h>
#include<fcntl.h> //open函数的头文件
#include<unistd.h> //read,close函数的头文件

#define SHOWHOST
void show_info(struct utmp *utbufp);
int main()
{
  struct utmp current_record; //读取utmp文件的结果保存在这里
  int utmpfd; //打开文件的文件标识符
  int reclen=sizeof(current_record);
  if((utmpfd=open(UTMP_FILE,O_RDONLY))==-1)
  {
    perror(UTMP_FILE);
    exit(1);
  }
  while(read(utmpfd,&current_record,reclen)==reclen)
    show_info(&current_record);
  close(utmpfd);
  return 0;
}

void show_info(struct utmp *utbufp)
{
  printf("%-8.8s",utbufp->ut_name);
  printf(" ");
  printf("%-8.8s",utbufp->ut_line);
  printf(" ");
  printf("%10ld",utbufp->ut_time);
  printf(" ");
  #ifdef SHOWHOST
    printf("(%s)",utbufp->ut_host);
  #endif
  printf("\n");
}
