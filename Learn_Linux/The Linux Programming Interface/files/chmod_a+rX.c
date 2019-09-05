#define _BSD_SOURCE
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include "tlpi_hdr.h"



int main(int argc, char *argv[])
{
    if(argc!=2)
        usageErr("use chmod_a+rX pathname!");
    
    struct stat s;
    if(stat(argv[1],&s)==-1)
        errExit("stat:%s",argv[1]);
    
    if(!s.st_mode&S_IFMT==S_IFDIR)
        usageErr("pathname needs to be a directory!");

    DIR *dir_ptr;
    struct dirent **dirlist;
    if((dir_ptr=opendir(argv[1]))==NULL)
        errExit("cannot open:%s",argv[1]);
    
    int size = scandir(argv[1],&dirlist,0,alphasort); //扫描这个目录所有的文件
    for(int i=0;i<size;i++)
    {
        if(strcmp(".",dirlist[i]->d_name)==0 || strcmp("..",dirlist[i]->d_name)==0)
            continue;
        char c[50];
        strcpy(c,argv[1]);
        //strcat(c,"/");
        strcat(c,dirlist[i]->d_name);
        printf("%s\n",c);
        if(stat(c,&s)==-1)
        {
            errExit("cannot stat %s",c);
        }
        if((s.st_mode&S_IFMT)==S_IFDIR)
        {
            if(chmod(c,S_IRUSR|S_IRGRP|S_IROTH|s.st_mode)==-1)
                errExit("cannot chmod %s",c);
        }
        else
        {
            if(chmod(c,S_IXUSR|S_IXGRP|S_IXOTH|s.st_mode)==-1)
                errExit("cannot chmod %s",c);
        }
        
    }



}