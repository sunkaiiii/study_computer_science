// reducto.c 一个简单的文件压缩程序
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LEN 40

int main(int argc, char *argv[])
{
    FILE *in, *out;
    int ch;
    char name[LEN];
    int count=0;

    if(argc<2)
    {
        fprintf(stderr,"Usage: %s filename\n",argv[0]);
        exit(EXIT_FAILURE);
    }
    if((in=fopen(argv[1],"r"))==NULL)
    {
        fprintf(stderr,"I could not open the file \"%s\"\n",argv[1]);
        exit(EXIT_FAILURE);
    }
    //设置输出
    strncpy(name,argv[1],LEN-5); //拷贝文件名
    name[LEN-5]='\0';
    strcat(name,".red");//在文件名后添加.red
    if((out=fopen(name,"w"))==NULL)
    {
        fprintf(stderr,"Cannot create output file.\n");
        exit(3);
    }
    while((ch=getc(in))!=EOF)
    {
        if(count++%3==0)
        {
            putc(ch,out);
        }
    }

    if(fclose(in)!=0||fclose(out)!=0)
    {
        fprintf(stderr,"Error in closing files\n");
    }

    return 0;
}