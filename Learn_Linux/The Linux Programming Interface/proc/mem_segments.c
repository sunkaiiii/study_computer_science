#include <stdio.h>
#include <stdlib.h>

char globBuf[65536]; //未初始化的数据段
int primes[]={2,3,5,7}; //初始化的数据段

static int square(int x) //分配的栈帧
{
    int result;
    result=x*x;
    return result;
}

static void doCalc(int val) //分配的栈帧
{
    printf("The square of %d\n", val, square(val));
    if(val<1000){
        int t;
        t=val*val*val;
        printf("The cube of %d is %d\n",val,t);
    }
}

int main(int argc, char *argv[]) //分配的栈帧
{
    static int key=9973; //初始化的数据段
    static char mbuf[10240000]; //未初始化的数据段
    char *p;

    p=malloc(1024); //返回指向堆的指针

    doCalc(key);

    exit(EXIT_SUCCESS);
}