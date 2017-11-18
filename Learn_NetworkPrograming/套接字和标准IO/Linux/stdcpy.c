#include<stdio.h>

#define BUF_SIZE 3

//使用标准IO
//速度快
int main(void)
{
    FILE *fp1;
    FILE *fp2;
    char buf[BUF_SIZE];
    fp1=fopen("/home/sunkai/下载/CLion-2017.3-RC.tar.gz","r");
    fp2=fopen("cpy.tar.tz","w");

    while(fgets(buf,BUF_SIZE,fp1)!=NULL)
        fputs(buf,fp2);
    fclose(fp1);
    fclose(fp2);
    return 0;
}
