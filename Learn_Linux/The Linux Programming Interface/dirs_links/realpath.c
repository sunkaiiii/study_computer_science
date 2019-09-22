#include <dirent.h>
#include <libgen.h>
#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>


#define BUF_SIZ 512

void walkDirs(char *result,__ino_t ino)
{
    struct stat sb;
    if(stat("..",&sb)==-1)
    {
        printf("stat: %s error","..");
        exit(EXIT_FAILURE);
    }
    if(sb.st_ino==ino)
    {
        strcat(result,"/");
    }else{
        walkDirs("..",sb.st_ino);
        chdir("..");
    }
    DIR *dirp;
    struct dirent *dp;
    dirp=opendir(".");
    for(;;)
    {
        dp=readdir(dp);
        if(dp==NULL)
        {
            break;
        }
        if(dp->d_ino==ino)
        {
            chdir(dp->d_name);
            strcat(result,"/");
            strcat(result,dp->d_name);
            break;
        }
    }
}

void findRealPath(char *name,char *reuslt)
{
    struct stat sb;
    if(stat(name,&sb)==-1)
    {
        printf("stat: %s error",name);
        exit(EXIT_FAILURE);
    }
    walkDirs(reuslt,sb.st_ino);
    printf("%s",reuslt);
}

int main(int argc, char *argv[])
{
    char *name;
    if(argc == 1)
    {
        name=".";
    }
    else
    {
        name=argv[1];
    }
    char result[BUF_SIZ];
    name=dirname(name);
    printf("%s",name);
    findRealPath(name,&result);
}