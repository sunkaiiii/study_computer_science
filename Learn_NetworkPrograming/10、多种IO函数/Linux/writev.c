#include<stdio.h>
#include<sys/uio.h>
#include<string.h>

int main(int argc,char *argv[])
{
    struct iovec vec[2]; //包含两个缓冲元素
    char buf1[]="ABCDEFG";
    char buf2[]="1235467";
    int str_len;
    vec[0].iov_base=buf1;
//    vec[0].iov_len=strlen(buf1);
    vec[0].iov_len=3;
    vec[1].iov_base=buf2;
//    vec[1].iov_len=strlen(buf2);
    vec[1].iov_len=3;
    str_len=writev(1,&vec,2); //向标准输出输出
    puts("");
    printf("Write bytes : %d\n",str_len);
    return 0;
}
