// floats.c--一些浮点型修饰符组合
#include <stdio.h>

int main(void)
{
    const double RENT=3852.99;

    printf("*%f*\n",RENT);
    printf("*%e*\n",RENT); //科学计数法
    printf("*%4.2f*\n",RENT);//宽度4，2位小数
    printf("*%3.1f*\n",RENT);//宽度3，且1位小数
    printf("*%10.3f*\n",RENT);//宽度10，3位小数
    printf("*%10.3E*\n",RENT);//宽度10，3位小数科学计数法
    printf("*%+4.2f*\n",RENT);//如果是正数，就显示+，负数显示-
    printf("*%010.2f*\n",RENT);//用前导0来表示10宽度的前导数
    
    return 0;
}