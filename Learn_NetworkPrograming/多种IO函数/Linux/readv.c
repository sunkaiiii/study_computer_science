#include<stdio.h>
#include<sys/uio.h>
#include<string.h>

#define BUF_SIZE 100

int main(int argc,char *argv[])
{
    struct iovec vec[2]; //包含两个缓冲元素
    char buf1[BUF_SIZE]={0,};
    char buf2[BUF_SIZE]={0,};
    int str_len;

    vec[0].iov_base=buf1;
    vec[0].iov_len=5; //第一个只写入5个
    vec[1].iov_base=buf2;
    vec[1].iov_len=BUF_SIZE; //第二个写入长度为BUF_SIZE

    str_len=readv(0,vec,2); //从标准输入获取信息，并一并写入
    printf("Read bytes:%d\n",str_len);
    printf("First message:%s\n",buf1);
    printf("Second message:%s\n",buf2);
    return 0;
}
