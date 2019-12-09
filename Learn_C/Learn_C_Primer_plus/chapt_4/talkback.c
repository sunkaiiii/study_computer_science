// talkback.c--演示用户交互
#include<stdio.h>
#include<string.h>
#define DENSITY 62.4

int main(void)
{
    float weight,volume;
    int size,letters;
    char name[40];

    printf("Hi What's your frist name?\n");
    scanf("%s",name); //这里name不用加&
    printf("%s, What's your weight in pounds?\n",name);
    scanf("%f",&weight);
    size=sizeof name;
    letters=strlen(name);
    volume=weight/DENSITY;
    printf("Well, %s, your volume is %2.2f cubic feet.\n",name,volume);
    printf("Also, your first name has %d letters,\n",letters);
}