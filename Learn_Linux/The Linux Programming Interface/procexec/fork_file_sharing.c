//在父子进程间共性文件偏移量和打开文件的状态标志
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include "tlpi_hdr.h"

int main(int argc,char *argv[])
{
    int fd,flags;
    char template[]="/tmp/testXXXXXX";

    setbuf(stdout,NULL);//关闭标准输出的缓冲

    fd=mkstemp(template);
    if(fd==-1)
        errExit("mkstemp");

    printf("O_APPEND flag before fork is: %s\n",(flags&&O_APPEND)?"on":"off");
    switch (fork())
    {
    case -1:
        errExit("fork");
        break;
    case 0: //子进程修改文件偏移量和标志,因为文件标识符共享，这也会影响到父进程
        if(lseek(fd,1000,SEEK_SET)==-1)
            errExit("lseek");
        flags=fcntl(fd,F_GETFL);
        if(flags==-1)
            errExit("fcntl-F_GETFL");
        flags|=O_APPEND;
        if(fcntl(fd,F_SETFL,flags)==-1)
            errExit("fcntl-F_SETFL");
        _exit(EXIT_SUCCESS);
    default:
        if(wait(NULL)==-1)
            errExit("wait");
        printf("Child has exited\n");
        printf("File offset in parent: %lld\n",(long long)lseek(fd,0,SEEK_CUR));
        flags=fcntl(fd,F_GETFL);
        if(flags==-1)
            errExit("fcntl-F_GETFL");
        printf("O_APPEND flag in parent is： %s\n",(flags&O_APPEND)?"on":"off");
        exit(EXIT_SUCCESS);
        break;
    }
}