#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>

int main(int argc,char *argv[])
{
  int status;
  pid_t pid=fork();

  if(pid==0)
  {
    return 3;
  }
  else
  {
    printf("child pid: %d\n",pid);
    pid=fork();
    if(pid==0)
    {
      exit(7);
    }
    else
    {
      printf("child pid :%d\n",pid);
      wait(&status);
      if(WIFEXITED(status))
        printf("Child sned one :%d\n",WEXITSTATUS(status));
      wait(&status); //因为之前创建了两个子进程，所以调用两次wait
      if(WIFEXITED(status))
        printf("Child sned one :%d\n",WEXITSTATUS(status));
      sleep(30);
    }
  }
}
