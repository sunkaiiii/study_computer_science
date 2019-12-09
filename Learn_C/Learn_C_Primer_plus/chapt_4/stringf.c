/*stringf.c--字符串格式*/
#include <stdio.h>
#define BLURB "Authentic imitation!"
int main(void)
{
    printf("[%2s]\n", BLURB);      
    printf("[%24s]\n", BLURB);      
    printf("[%24.5s]\n", BLURB);//24的宽度，但是只输出5个字符  
    printf("[%-24.5s]\n", BLURB); //24宽度，输出5个字符，左对齐
  
    return 0;
}