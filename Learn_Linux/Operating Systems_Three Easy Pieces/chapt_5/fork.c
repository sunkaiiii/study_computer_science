#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main(int argc, char *argv)
{
    printf("Hello world (pid:%d)\n",(int)getpid());
    int rc=fork();
    if(rc<0)
    {
        fprintf(stderr,"fork failed\n");
        exit(1);
    }else if(rc==0)
    {
        printf("hellp, I am child (pid:%d)\n",(int)getpid());
    }else
    {
        printf("hello, I am parrent of %d (pid:%d)",rc,(int)getpid());   
    }
    return 0;
}