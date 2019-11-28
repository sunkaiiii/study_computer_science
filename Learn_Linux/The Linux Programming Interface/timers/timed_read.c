#include <signal.h>
#include "tlpi_hdr.h"

#define BUF_SIZE 200

static void handler(int sig) 
{
    printf("Caught signal\n");
}

int main(int argc,char *argv[])
{
    struct sigaction sa;
    char buf[BUF_SIZE];
    ssize_t numRead;
    int savedErrno;

    if(argc>1 && strcmp(argv[1],"--help")==0)
        usageErr("%s [num-secs [restart-flag]]\n",argv[0]);
    
    //设置SIGALRM的handler，允许系统调用被中断，除非已经执行完毕
    sa.sa_flags=(argc>2)?SA_RESTART:0; //如果没有指明，则收到信号后不重启read
    sigemptyset(&sa.sa_mask);
    sa.sa_handler=handler;
    if(sigaction(SIGALRM,&sa,NULL)==-1)
        errExit("sigaction");
    
    alarm((argc>1)?getInt(argv[1],GN_NONNEG,"num-secs"):10);
    
    numRead=read(STDIN_FILENO,buf,BUF_SIZE-1);

    savedErrno=errno; //防止alarm()修改它
    alarm(0); //重置alarm()
    errno=savedErrno;
    
    if(numRead==-1)
        if(errno==EINTR)
            printf("Read timed out\n");
        else
            errMsg("read");
    else
    {
        printf("Successful read (%ld bytes): %.*s",(long)numRead,(int)numRead,buf);
    }
    exit(EXIT_SUCCESS);
    
}