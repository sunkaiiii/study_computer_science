// cypher1.c -- 更改输入，空格不变
#include <stdio.h.>
#define SPACE ' '
int main(void)
{
    char ch;

    ch=getchar();
    while (ch!='\n')
    {
        if(ch==SPACE)
            putchar(ch);
        else
            putchar(ch+1); //改变为其他字符
        ch=getchar(); //获取下一个字符
    }
    putchar(ch);

    return 0;
}