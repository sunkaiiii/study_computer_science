//useheader.c -- 使用names_st结构
#include<stdio.h>
#include"names_st.h"
//编译时链接names_st.c

int main(void)
{
    names candidate;
    get_names(&candidate);
    printf("Let's welcome");
    show_names(&candidate);
    printf(" to this program!\n");
    return 0;
}