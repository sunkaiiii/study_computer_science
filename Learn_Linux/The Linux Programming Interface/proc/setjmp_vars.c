#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>

static jmp_buf env;

static void doJump(int nvar, int rvar, int vvar)
{
    printf("Inside doJump():nvar=%d rvar=%d vvar=%d\n",nvar,rvar,vvar);
    longjmp(env,1);
}

//某些应用程序二进制接口（ABI）实现的语义要求
//longjmp()函数恢复先前setjmp()调用所保存的cpu寄存器副本
//这就意味着longjmp()操作会致使经过优化的变量被赋以错误的值
//需要将变量声明为volatile，避免编译器优化
int main(int argc,char *argv[])
{
    volatile int nvar;
    volatile int rvar;
    volatile int vvar; //声明编译器不要为他优化
    nvar=111;
    rvar=222;
    vvar=333;
    if(setjmp(env)==0) //初始化
    {
        nvar=777;
        rvar=888;
        vvar=999;
        doJump(nvar,rvar,vvar);
    }else{
        printf("After longjmp(): nvar=%d rvar=%d vvar=%d\n",nvar,rvar,vvar);
    }
    exit(EXIT_SUCCESS);

}