#include "tlpi_hdr.h"

extern char **environ;

//显示进程的环境变量
int main(int argc,char *argv){
    char **ep;

    for(ep=environ;*ep!=NULL;ep++){
        puts(*ep);
    }

    exit(EXIT_SUCCESS);
}