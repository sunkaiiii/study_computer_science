/* while2.c -- 注意分号的位置*/
#include<stdio.h>
int main(void)
{
    int n=0;
    while(n++<3);  //跟着一个分号，会认为是一个语句，于是他不会执行下面哪一行内容
        printf("n is %d\n",n);
    printf("That's all this program does.\n");

    return 0;
}