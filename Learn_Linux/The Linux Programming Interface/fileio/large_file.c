#define _LARGEFILE64_SOURCE
#define _FILE_OFFSET_BITS 64 //使用这个宏的时候，open等操作都会对应为64位的方法
#include <sys/stat.h>
#include <fcntl.h>
#include "tlpi_hdr.h"

//使用64位API操作大文件
int main(int argc, char *argv){
    int fd;
    off64_t off;
    if(argc!=3||strcmp(argv[1],"--help")==0)
        usageErr("%s pathname offset\n",argv[0]);
    
    fd=open(argv[1],O_RDWR|O_CREAT,S_IRUSR|S_IWUSR);
    if(fd==-1)
        errExit("open64");
    
    off=atoll(argv[2]);

    if(lseek(fd,off,SEEK_SET)==-1)
        errExit("lseek64");
    
    if(write(fd,"test",4)==-1)
        errExit("write");
    
    exit(EXIT_SUCCESS);
}