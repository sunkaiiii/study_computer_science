//在main()以及信号处理函数中调用不可重入函数
#define _XOPEN_SOURCE 600
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include "tlpi_hdr.h"

static char *str2;
static int handled=0;

static void handler(int sig)
{
    crypt(str2,"xx");
    handled++;
}

int main(int argc,char *argv[])
{
    char *cr1;
    int callNum, mismatch;
    struct sigaction sa;

    if(argc!=3)
    {
        usageErr("%s str1 str2\n",argv[0]);
    }
    str2=argv[2];
    cr1=strdup(crypt(argv[1],"xx"));
    if(cr1==NULL)
    {
        errExit("strdup");
    }
    sigemptyset(&sa.sa_mask);
    sa.sa_flags=0;
    sa.sa_handler=handler;
    if(sigaction(SIGINT,&sa,NULL)==-1)
        errExit("sigaction");
    //重复调用crtpy()。如果这时候触发SIGINT，若此时正好发生在41行刚刚执行crypt()之后，crypt()静态存储区将会被argv[2]加密的结果覆盖，从而导致strcmp失败
    for(callNum=1,mismatch=0;;callNum++)
    {
        if(strcmp(crypt(argv[1],"xx"),cr1)!=0)
        {
            mismatch++;
            printf("Mismatch on call %d (mismatch=%d handled=%d)\n",callNum,mismatch,handled);
        }
    }
}