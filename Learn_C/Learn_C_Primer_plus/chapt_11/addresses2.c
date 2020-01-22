//addresses2.c -- 数组和指针字符串的区别以及错误应用
#include<stdio.h>
int main(void)
{
    char *p1="Klingon";
    p1[0]='F'; //ok?
    printf("Klingon");
    printf(":Beware the %ss!\n","Klingon");

    return 0;
}