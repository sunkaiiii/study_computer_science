/*skiptwo.c--跳过输入中的前两个整数*/
#include<stdio.h>
int main(void)
{
    int n;

    printf("Please enter three integers:\n");

    scanf("%*d %*d %d",&n); //跳过前两个输入
    printf("The last integer was %d\n",n);

    return 0;
}