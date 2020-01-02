//备选拼写：iso646.h
#include<stdio.h>
#include<iso646.h>
int main(void)
{
    int num;
    scanf("%d",&num);

    if((num>0 and num<100) or num ==-1 or not(num%3==0)) //使用iso646的头文件替换符号
    {
        printf("%d\n",num);
    }

    return 0;
}