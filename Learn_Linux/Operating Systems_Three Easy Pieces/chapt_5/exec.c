#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/wait.h>

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
        char *myArgs[3];
        myArgs[0]=strdup("ls");
        myArgs[1]=strdup(".");
        myArgs[2]=NULL;
        execvp(myArgs[0],myArgs);
        printf("this shouldn't print out");
    }else
    {
        int wc=wait(NULL);
        printf("hello, I am parrent of %d (wc:%d) (pid:%d)",wc,rc,(int)getpid());   
    }
    return 0;
}