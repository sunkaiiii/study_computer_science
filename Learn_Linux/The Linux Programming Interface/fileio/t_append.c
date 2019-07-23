#include <sys/stat.h>
#include <fcntl.h>
#include "tlpi_hdr.h"

int main(int argc,char *argv[]){
    int fd=open("a.txt",O_WRONLY|O_APPEND);
    if(fd==-1){
        errExit("open");
    }
    lseek(fd,0,SEEK_SET); //将偏移量置为文件开头
    char *a="abcdefg\n";
    int numWrite;
    numWrite=write(fd,a,sizeof(a));
    if(numWrite==-1)
        errExit("write");
    if(numWrite<sizeof(a))
        printf("write number is fewer than buffer\n");
    exit(EXIT_SUCCESS); 
}