#include<stdio.h>
#include<unistd.h>
#define BUF_SZIE 30
//管道的双向通信

int main(int argc,char *argv[])
{
  int fds[2];
  char str1[]="Who are you?";
  char str2[]="Thank you for you meesage!";
  char buf[BUF_SZIE];
  pid_t pid;

  pipe(fds);
  pid=fork();
  if(pid==0) //自进程向管道写入，睡眠一段时间之后从管道取
  {
    write(fds[1],str1,sizeof(str1));
    sleep(2);
    read(fds[0],buf,BUF_SZIE);
    printf("child proc output:%s\n",buf);
  }
  else
  {
    read(fds[0],buf,BUF_SZIE);
    printf("Parent proc output:%s\n",buf);
    write(fds[1],str2,sizeof(str2));
    sleep(3);
  }
  return 0;

}
