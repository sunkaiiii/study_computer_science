#define _BSD_SOURCE
#define _XOPEN_SOURCE
#include <unistd.h>
#include <limits.h>
#include <pwd.h>
#include <shadow.h> //似乎默认配置下的Mac没发启用这个
#include "tlpi_hdr.h"

int main(int argc,char *argv[])
{
    char *username, *password, *encrypted, *p;
    struct passwd *pwd;
    struct swpd *swpd;
    Boolean authOK;
    size_t len;
    long lnmax;
    lnmax=sysconf(_SC_LOGIN_NAME_MAX);
    if(lnmax==-1)
        lnmax=256; //做个猜测
    username=malloc(lnmax);
    if(username==NULL)
        errExit("malloc");
    printf("Username: ");
    fflush(stdout);
    if(fgets(username,lnmax,stdin)==NULL)
        exit(EXIT_FAILURE);
    
    len=strlen(username);
    if(username[len-1]=='\n')
        username[len-1]='\0'; //去掉换行符
    pwd=getpwnam(username);
    if(pwd==NULL)
        fatal("could not get password record");
    spad=getspnam(username);
    if(swpd==NULL && errno==EACCES)
        fatal("no permission to read shadow password file");
    if(swpd != NULL) //如果找到了shadowPassword
        pwd->pw_passwd=spwd->sp_pwdp; //用这个shadowPassword
    password=getpass("Password: ");
    //加密密码并立即清除纯文本的记录
    encrypted=crypt(password,pwd->pw_passwd);
    for(p=password;*p!='\0';)
        *p++='\0';
    if(encrypted==NULL)
        errExit("crtpt");
    authOK=strcmp(encrypted,pwd->pw_passwd)==0;
    if(!authOK)
    {
        printf("incorrect password\n");
        exit(EXIT_FAILURE);
    }
    printf("Successfully autheticated: UID=%ld\n",(long)pwd->pw_uid);
    exit(EXIT_SUCCESS);
}