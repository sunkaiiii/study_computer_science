#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>
//编写一个程序，观察当使用longjmp()函数跳转到一个已经返回的函数时会怎么样
//-O1优化引发段错误，-O2优化引发无限执行
static jmp_buf env;
static void f1(){
    if(setjmp(env)==0){
        printf("init setjmp\n");
    }else{
        printf("longjmp return\n");
    }
}

static void f2(){
    longjmp(env,2);
}

int main(int argc,char *argv[]){
    f1();
    f2();
    f2();
    f2();
    f2();
    f2();
    f2();
    f2();
}