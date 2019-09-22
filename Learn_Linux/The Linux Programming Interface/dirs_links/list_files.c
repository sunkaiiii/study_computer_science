#include<dirent.h>
#include "tlpi_hdr.h"

static void listFiles(const char *dirpath)
{
    DIR *dirp;
    struct dirent *dp;
    Boolean isCurrent; //当是.的时候，返回true
    isCurrent=strcmp(dirpath,".")==0;
    dirp=opendir(dirpath);
    if(dirp==NULL)
    {
        errMsg("opendir failed on %s",dirpath);
        return;
    }

    //对这个进行循环，打印目录+文件名
    for(;;)
    {
        errno=0;
        dp=readdir(dirp);
        if(dp==NULL)
            break;
        if(strcmp(dp->d_name,".")==0||strcmp(dp->d_name,"..")==0)
            continue; //跳过.和..
        if(!isCurrent)
            printf("%s/",dirpath);
        printf("%s\n",dp->d_name);
    }

    if(errno!=0)
        errExit("readdir");
    if(closedir(dirp)==-1)
        errMsg("closedir");
}

int main(int argc, char *argv[])
{
    if(argc>1&&strcmp(argv[1],"--help")==0)
        usageErr("%s [dir...]\n",argv[0]);
    if(argv==1)
        listFiles(".");
    else
        for(argv++;*argv;argv++)
            listFiles(*argv);
    exit(EXIT_SUCCESS);
}