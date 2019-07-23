#include <sys/stat.h>
#include <fcntl.h>
#include "tlpi_hdr.h"

//使用fcntl模拟dup和dup2
int main(int argc,char *argv[]){
    int fd=open(argv[1],O_WRONLY|O_APPEND);
    if(fd==-1){
        errExit("open");
    }
    if(fcntl(fd,F_GETFL,O_WRONLY|O_APPEND)==-1){ //检验文件描述符是否有效
        errExit("fcntlCheck");
    }
    int setfd=fd+1;
    if(argc==3){
        int a=0;
        for(int i=0;argv[2][i]!='\0';i++){
            a=a*10+(argv[2][i]-'0');
        }
        setfd=a;
    }
    printf("%d\n",setfd);
    //使用fcntl来复制文件描述符
    int newfd=fcntl(fd,F_DUPFD,setfd);
    printf("%d\n",newfd);
    if(newfd==-1){
        errExit("fcntl");
    }
    write(newfd,"123",sizeof("123"));
    close(fd);
    close(newfd);
    exit(EXIT_SUCCESS);
}