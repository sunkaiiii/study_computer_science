#include <sys/stat.h>
#include <fcntl.h>
#include "tlpi_hdr.h"

/*
这个程序有个潜在的问题
当第一次调用open时，希望打开的文件还不存在
而当第二次调用open时，其他文件已经创建了该文件
这就会导致两个进程都会认为是自己创建的文件
这种并发时候的错误其实还是很常见的
 */
int main(int argc,char *argv[]){
    int fd=open(argv[1],O_WRONLY);
    if(fd!=-1){
        printf("[PID %ld] File \"%s\" already exists\n",(long)getpid(),argv[1]);
        close(fd);
    }else{
        if(errno!=ENOENT){
            errExit("open");
        }else{
            /*失败窗口 */
            fd=open(argv[1],O_WRONLY|O_CREAT,S_IRUSR|S_IWUSR);
            if(fd==-1)
                errExit("open");
                
            printf("[PID %ld] Created file \"%s\" exclusively \n",(long)getpid(),argv[1]);
        }
    }
}