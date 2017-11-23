#include<stdio.h>
#include <fcntl.h>

#define BUF_SIZE 3

//使用fdopen将文件描述符转换为FILE*指针
int main(void)
{
    FILE *fp;
    int fd=open("data.dat",O_WRONLY|O_CREAT|O_TRUNC);
    fp=fdopen(fd,"w");
    fputs("Network c programming\n",fp);
    fclose(fp);
    return 0;
}
