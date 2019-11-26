//使用备选信号栈来处理栈溢出时候的情况
#define _GNU_SOURCE
#include <string.h>
#include <signal.h>
#include "tlpi_hdr.h"

static void sigsegvHandler(int sig)
{
    int x;
    printf("Caught signal %d (%s)\n",sig,strsignal(sig));
    printf("Top of handler stack near %10p\n",(void*)&x);
    fflush(NULL);
    _exit(EXIT_FAILURE);
}

//通过一个递归，触发栈溢出
static void overflowStack(int callNum)
{
    char a[100000];
    printf("Call %4d - top of stack near %10p\n",callNum,&a[0]);
    overflowStack(callNum+1);
}

int main(int argc, char *argv[])
{
    stack_t sigstack;
    struct sigaction sa;
    int j;

    printf("Top of standard stack is near %10p\n",(void*)&j);
    //分配备选信号栈
    sigstack.ss_sp=malloc(SIGSTKSZ);
    if(sigstack.ss_sp==NULL)
        errExit("malloc");
    sigstack.ss_size=SIGSTKSZ;
    sigstack.ss_flags=0;
    if(sigaltstack(&sigstack,NULL)==-1)
        errExit("sigaltstack");
    printf("Alternate stack is at %10p-$p\n",sigstack.ss_sp,(char*)sbrk(0)-1);
    sa.sa_handler=sigsegvHandler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags=SA_ONSTACK;
    if(sigaction(SIGSEGV,&sa,NULL)==-1)
        errExit("sigaction");
    overflowStack(1);
}