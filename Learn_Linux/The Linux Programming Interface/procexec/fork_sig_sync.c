//利用信号来同步进程间动作
#include <signal.h>
#include "tlpi_hdr.h"

#define SYNC_SIG SIGUSR1 //同步信号

static void handler(int sig)
{}

int main(int argc,char *argv[])
{
    pid_t childPid;
    sigset_t blockMask, origMask, emptyMask;
    struct sigaction sa;

    setbuf(stdout,NULL);
    sigemptyset(&blockMask);
    sigaddset(&blockMask,SYNC_SIG);
    if(sigprocmask(SIG_BLOCK,&blockMask,&origMask)==-1)
        errExit("sigprocmask");
    sigemptyset(&sa.sa_mask);
    sa.sa_flags=SA_RESTART;
    sa.sa_handler=handler;
    if(sigaction(SYNC_SIG,&sa,NULL)==-1)
        errExit("sigaction");
    switch(childPid=fork())
    {
        case -1:
            errExit("fork");
        case 0:
            //子进程做一些操作
            printf("[%ld] Child started - dome some work\n",(long)getpid());
            sleep(2);
            //通知父进程
            printf("[%ld] Child about to singal parent\n",(long)getpid());
            if(kill(getpid(),SYNC_SIG)==-1)
                errExit("kill");
            _exit(EXIT_SUCCESS);
        default:
            printf("[%ld] Parent about to wait for signal\n",(long)getpid());
            sigemptyset(&emptyMask);
            if(sigsuspend(&emptyMask)==-1&&errno !=EINTR) //挂起进程，等待一个信号
                errExit("sigsuspend");
            printf("[%ld] Parent got signal\n",(long)getpid());
            //恢复原来的mask
            if(sigprocmask(SIG_SETMASK,&origMask,NULL)==-1)
                errExit("sigprocmask");
            exit(EXIT_SUCCESS);
    }

}