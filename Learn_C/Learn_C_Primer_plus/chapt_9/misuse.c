/*misuse.c -- 错误的使用函数*/
#include <stdio.h>
int imax(); /*就是函数声明*/
//这是一个可以运行的程序
//但是会输出错误的结果，造成这个的原因就是因为程序没有使用函数原型
int main(void)
{
    printf("The maximum of %d and %d is %d.\n",3,5,imax(3));
    printf("The maximum of %d and %d is %d.\n",3,5,imax(3.0,5.0));
    return 0;
}

int imax(n,m)
int n,m;
{
    return (n>m?n:m);
}