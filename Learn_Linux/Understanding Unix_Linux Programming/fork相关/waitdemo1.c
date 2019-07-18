/*展示父进程创建玩子进程后等待子进程退出*/
#include<stdio.h>

#define DELAY 2

int main()
{
  int newpid;
  void child_code(),parent_code();
  printf("before : my pid is %d\n",getpid());
  if((newpid=fork())==-1)
    perror("fork");
  else if(newpid==0)
    child_code(DELAY);
  else
    parent_code(newpid);
}

void child_code(int delay)
{
  printf("child %d here,will sleep for %d seconds\n",getpid(),delay);
  sleep(delay);
  printf("child done.about to exit\n");
  exit(17);
}

/*父进程的等待子进程运行结束，并返回消息*/
void parent_code(int childpid)
{
  int wait_rv; //从wait中获取返回值
  wait_rv=wait(NULL);
  printf("done waiting for %d.Wait returned:%d\n",childpid,wait_rv);
}
