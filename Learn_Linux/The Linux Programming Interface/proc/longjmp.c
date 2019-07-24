#include <setjmp.h>
#include "tlpi_hdr.h"

static jmp_buf env;

static void f2(void)
{
    longjmp(env,2);
}

static void f1(int argc)
{
    if(argc==1)
        longjmp(env,1);
    f2();
}

//通过setjump设置初始调用目标
//通过switch检测setjmp()调用的返回值
//用于检测是初次setjmp返回还是longjmp返回
//当setjmp调用为0时，将调用f1
//f1根据参数数量来决定调用longjmp还是f2
//如果调用f2，她会马上调用longjump
//由于设置了不同的env值，会根据不同的值进入switch
int main(int argc, char * argv[])
{
    switch (setjmp(env))
    {
    case 0: //这是第一次初始化setjmp()之后的返回值
        printf("Calling f1() after initial setjmp()\n");
        f1(argc);
        break;
    case 1:
        printf("We jumped back from f1()\n");
    break;
    case 2:
        printf("We jumped back from f2()\n");
        break;
    }
    exit(EXIT_SUCCESS);
}