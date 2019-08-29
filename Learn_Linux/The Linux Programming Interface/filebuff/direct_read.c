#define _GNU_SOURCE
#include <fcntl.h>
#include <malloc.h>
#include "tlpi_hdr.h"

int main(int argc,char *argv[])
{
    int fd;
    ssize_t numRead;
    size_t length, alignment;
    off_t offset;
    void *buf;

    if(argc<3||strcmp(argv[1],"--help")==0)
        usageErr("%s file length [offset [alignment]]\n",argv[0]);
    length=getLong(argv[2],GN_ANY_BASE,"offset");
    offset=(argc>3)?getLong(argv[3],GN_ANY_BASE,"offset"):0;
    alignment=(argc>4)?getLong(argv[4],GN_ANY_BASE,"alignment"):4096;

    fd=open(argv[1],O_RDONLY|O_DIRECT);
    if(fd==-1)
        errExit("open");
    /* memalign（）分配一个与第一个参数的倍数相对应的地址块。 以下表达式确保'buf'在'alignment'的非幂次数上对齐。 我们这样做是为了确保例如，如果我们要求一个256字节的对齐缓冲区，那么我们不会意外得到
    缓冲区，也在512字节边界上对齐。需要'（char *）'强制转换才能允许指针运算（这在memalign（）返回的'void *'上是不可能的）。
    */
   buf=(char *)memalign(alignment*2,length+alignment)+alignment;
   if(buf==NULL)
        errExit("memalign");
   if(lseek(fd,offset,SEEK_SET)==-1)
        errExit("lseek");
    numRead=read(fd,buf,length);
    if(numRead==-1)
        errExit("read");
    printf("Read %ld bytes\n",(long)numRead);

    exit(EXIT_SUCCESS);
}