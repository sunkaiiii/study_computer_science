/*who3.c
实现了who命令的第三个程序版本，添加了缓冲区，增加了程序的执行效率
*/
#include<stdio.h>
#include<utmp.h>
#include<fcntl.h> //open函数的头文件
#include<unistd.h> //read,close函数的头文件
#include<time.h>
#include<sys/types.h>


#define SHOWHOST
#define NRECS 16
#define NULLUT ((struct utmp *)NULL)
#define UTSIZE (sizeof(struct utmp))

static char utmpbuf[NRECS * UTSIZE];
static int num_recs;
static int cur_rec;
static int fd_utmp=-1;

void show_info(struct utmp *utbufp);
void show_time(long timeval);

int utmp_open(char *filename)
{
  fd_utmp=open(filename,O_RDONLY);
  cur_rec=num_recs=0;
  return fd_utmp;
}

int utmp_reload()
/*
读取下一个记录
*/
{
  int amt_read;
  amt_read=read(fd_utmp,utmpbuf,NRECS*UTSIZE);
  num_recs=amt_read/UTSIZE;
  cur_rec=0;
  return num_recs;
}

void utmp_close()
{
  if(fd_utmp!=-1)
    close(fd_utmp);
}

struct utmp *utmp_next()
{
  struct utmp *recp;
  if(fd_utmp==-1)
    return NULLUT;
  if(cur_rec==num_recs&&utmp_reload()==0)
    return NULLUT;

  recp=(struct utmp*)&utmpbuf[cur_rec*UTSIZE];
  cur_rec++;
  return recp;
}

int main()
{
  struct utmp *utbufp,*utmp_next();
  if(utmp_open(UTMP_FILE)==-1)
  {
    perror(UTMP_FILE);
    exit(1);
  }
  while((utbufp=utmp_next())!=((struct utmp*)NULL))
    show_info(utbufp);
  utmp_close();
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
