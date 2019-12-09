/* width.c--字段宽度*/
#include<stdio.h>
#define PAGES 959
int main(void)
{
    printf("*%d*\n",PAGES);
    printf("*%2d*\n",PAGES); //2宽度
    printf("*%10d*\n",PAGES);//10宽度
    printf("*%-10d*\n",PAGES);//左对齐10距离

    return 0;
}