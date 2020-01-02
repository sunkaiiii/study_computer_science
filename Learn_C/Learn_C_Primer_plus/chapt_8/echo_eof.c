/* echo_eof.c -- 重复输入，知道文件结尾*/
#include<stdio.h>
int main(void)
{
    int ch;

    while((ch=getchar())!=EOF) //getchar和putchar都支持文件重定位
        putchar(ch);
    
    return 0;
}