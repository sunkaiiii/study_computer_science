//为两个不同的信号建立统一处理函数
#include <signal.h>
#include <sys/types.h>
#include <stdio.h> 
#include <stdlib.h>

#include <unistd.h> 
#include <errno.h> 
#include <string.h> 

static void sigHandler(int sig)
{
    static int count=0;
    //这个handler用了非异步安全的信号方法
    if(sig==SIGINT)
    {
        count++;
        printf("Caught SIGINT (%d)\n",count);
        return;
    }

    printf("Caught SIGQUIT - that's all folks");
    exit(EXIT_SUCCESS);
}

int main(int argc,char *argv)
{
    signal(SIGINT,sigHandler);
    signal(SIGQUIT,sigHandler);
    for(;;)
        pause();
}