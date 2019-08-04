#define _XOPEN_SOURCE
#include <time.h>
#include <locale.h>
#include "tlpi_hdr.h"

#define SBUF_SIZE 1000

int main(int argc, char *argv[])
{
    struct tm tm;
    char sbug[SBUF_SIZE];
    char *ofmt;

    if(argc<3||strcmp(argv[1],"--help")==0)
        usageErr("%s input-data-time in-format [out-format]\n",argv[0]);
    if(setlocale(LC_ALL,"")==NULL)
        errExit("setlocale"); //使用本地的设置
    memset(&tm,0,sizeof(struct tm)); //初始化
    if(strptime(argv[1],argv[2],&tm)==NULL)
        fatal("strptime");
    tm.tm_isdst=-1; //不用设置strptime()，告诉mktime()函数去决定DST就已经很有效了
    printf("calendar time (seconds since Epoch):%ld\n",(long)mktime(&tm));
    
    ofmt=(argc>3)?argv[3]:"%H:%M:%S:%A, %d %B %Y %Z";
    if(strftime(sbug,SBUF_SIZE,ofmt,&tm)==0)
        fatal("strftime returned 0");
    printf("strftime() yields: %s\n", sbug);
    exit(EXIT_SUCCESS);
}