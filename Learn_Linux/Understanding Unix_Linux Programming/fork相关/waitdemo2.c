/*
展示父进程创建玩子进程后等待子进程退出
waitdemo2将额外显示子进程退出时候的状态
*/
#include<stdio.h>

#define DELAY 5

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
  /*
  ×将一个整形变量传入给wait函数，返回子进程退出时候的状态
  *整数变量由三部分组成，高位8个bit记录退出值，低位7个bit记录信号序号，中间的1个bit用来指明发生错误并产生了内核映像
  */
  int wait_rv; //从wait中获取返回值
  int child_status;
  int high_8,low_7,bit_7;
  wait_rv=wait(&child_status);
  printf("done waiting for %d.Wait returned:%d\n",childpid,wait_rv);
  high_8=child_status>>8; /*1111 1111 0000 0000*/
  low_7=child_status&0x7F; /*0000 0000 0111 1111*/
  bit_7=child_status&0x80; /*0000 0000 1000 0000*/
  printf("status:exit=%d,sig=%d,core=%d\n",high_8,low_7,bit_7);
}
