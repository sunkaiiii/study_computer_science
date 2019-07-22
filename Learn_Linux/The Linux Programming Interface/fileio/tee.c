//
//  tee.c
//  LearnLinux
//
//  Created by 孙楷 on 22/7/19.
//  Copyright © 2019 孙楷. All rights reserved.
//

#include <sys/stat.h>
#include <fcntl.h>
#include <ctype.h>
#include "tlpi_hdr.h"

#ifndef BUF_SZE
#define BUF_SIZE 1024
#endif

//tee命令是从标准输入中读取数据，直至文件结尾。随后将数据j写入标准输出和参数指定的文件。
//-a命令会向一个已有的文件追加数据
int main(int argc,char *argv[])
{
    if(argc<2)
        usageErr("need a file name: %s",argv[0]);
    int outputFd;
    int openFlags=O_CREAT|O_WRONLY|O_TRUNC;
    char *filename=argv[1];
    if(argc==3)
    {
        if(strcmp(argv[1], "-a")!=0)
            cmdLineErr("you should use -a:%s ",argv[1]);
        openFlags=O_WRONLY|O_APPEND;
        filename=argv[2];
    }
    int filePerms=S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH;
    outputFd=open(filename,openFlags,filePerms);
    char buf[BUF_SIZE];
    size_t numRead;
    while((numRead=read(STDIN_FILENO, buf, BUF_SIZE))>0)
    {
        if(write(STDOUT_FILENO, buf, numRead)<numRead)
            fatal("could not write buffer to stdout");
        if(write(outputFd, buf, numRead)<numRead)
            fatal("could not write to file");
    }
    if(close(outputFd)==-1)
        errExit("close");
    exit(EXIT_SUCCESS);
}
