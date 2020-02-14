//generic.c -- 定义泛型宏
#include <stdio.h>
#include <math.h>
#define RAD_TO_DEG (180/(4*atanl(1)))

//反省平方根函数
#define SQRT(X) _Generic((X),\
    long double:sqrtl,\
    default:sqrt,\
    float:sqrtf)(X)

//反省正弦函数，角度的单位为度
#define SIN(X) _Generic((X),\
    long double:sinl((X)/RAD_TO_DEG),\
    default: sin((X)/RAD_TO_DEG),\
    float: sinf((X)/RAD_TO_DEG)\
)

int main(void)
{
    float x=45.0f;
    double xx=45.0;
    long double xxx=45.0L;

    long double y=SQRT(x); //匹配float
    long double yy=SQRT(xx); //匹配default
    long double yyy=SQRT(xxx); //匹配long double
    printf("%.1fLf\n",y);
    printf("%.1fLf\n",yy);
    printf("%.1fLf\n",yyy);
    int i=45;
    yy=SQRT(i);
    printf("%.17Lf\n",yy);
    yyy=SIN(xxx);
    printf("%.17Lf\n",yyy);

    return 0;
}