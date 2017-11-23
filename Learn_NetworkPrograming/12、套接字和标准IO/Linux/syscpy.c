#include<stdio.h>
#include<fcntl.h>
#include <unistd.h>

#define BUF_SIZE 3

//使用系统的write和read来复制文件
//速度将会很慢
int main(void)
{
    int fd1,fd2;
    int len;
    char buf[BUF_SIZE];

    fd1=open("/home/sunkai/下载/CLion-2017.3-RC.tar.gz",O_RDONLY);
    fd2=open("cpy.tar.gz",O_WRONLY|O_CREAT|O_TRUNC);

    while((len=read(fd1,buf,sizeof(buf)))>0)
        write(fd2,buf,len);
    close(fd1);
    close(fd2);
    return 0;
}
