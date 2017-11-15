#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>

int main(int argc,char *argv[])
{
  int status;
  pid_t pid=fork();
  if(pid==0)
  {
    sleep(15);
    return 24;
  }
  else
  {
    while(!waitpid(pid,&status,WNOHANG)) //传递WNOHANG之后，waitpid便不会阻塞主线程，他会在循环中执行put
    {
      sleep(3);
      puts("sleep 3 sec\n");
    }
    if(WIFEXITED(status))
      printf("Child send %d\n",WEXITSTATUS(status));
  }
  return 0;
}
