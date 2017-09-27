/*who2.c
实现了who命令的第二个程序版本，过滤掉了空白记录，只显示已登录的用户，并显示登录时间
*/
#include<stdio.h>
#include<utmp.h>
#include<fcntl.h> //open函数的头文件
#include<unistd.h> //read,close函数的头文件
#include<time.h>

#define SHOWHOST
void show_info(struct utmp *utbufp);
void show_time(long timeval);
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
  if(utbufp->ut_type!=USER_PROCESS)
    return;
  printf("%-8.8s",utbufp->ut_name);
  printf(" ");
  printf("%-8.8s",utbufp->ut_line);
  printf(" ");
  show_time(utbufp->ut_time);
  #ifdef SHOWHOST
    printf("(%s)",utbufp->ut_host);
  #endif
  printf("\n");
}
void show_time(long timeval) //将传递过来的time_t类型数据转换为时间字符
{
  char *cp;
  cp=ctime(&timeval);
  printf("%12.12s",cp+4);
}
