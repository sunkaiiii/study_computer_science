//为SIGINT信号安装一个处理器程序
#include <signal.h>
#include <sys/types.h>
#include <stdio.h> 
#include <stdlib.h>

#include <unistd.h> 
#include <errno.h> 
#include <string.h> 
static void sigHandler(int sig)
{
    printf("Ouch\n");
}

int main(int argc, char *argv[])
{
    int j;
    if(signal(SIGINT, sigHandler)==SIG_ERR)
    {
        printf("error");
        exit(1);
    }

    for(j=0;;j++)
    {
        printf("%d\n",j);
        sleep(3);
    }
}