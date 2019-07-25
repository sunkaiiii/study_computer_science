#include <pwd.h>
#include <grp.h>
#include <ctype.h>
#include "ugid_functions.h"

char *userNameFromId(uid_t uid) //返回符合uid的name
{
    struct passwd *pwd;
    pwd=getpwuid(uid);
    return pwd==NULL?NULL:pwd->pw_name;
}

uid_t userIdFromName(const char *name) //返回符合UID的用户名
{
    struct passwd *pwd;
    uid_t u;
    char *endptr;
    if(name==NULL||*name=='\0')
        return -1;
    u=strtol(name, &endptr,10);
    if(*endptr=='\0')
        return u;
    
    pwd=getpwnam(name);
    if(pwd==NULL)
        return -1;
    return pwd->pw_uid;
}

char* groupNameFromId(gid_t gid) //返回符合gid的group name
{
    struct group *grp;
    grp=getgrgid(gid);
    return grp==NULL?NULL:grp->gr_name;
}

gid_t groupIdFromName(const char *name) //返回符合name的gid
{
    struct group *grp;
    gid_t g;
    char *endptr;

    if(name == NULL||*name=='\0')
        return -1;
    
    g=strtol(name,&endptr,10);
    if(*endptr=='\0')
        return g;
    
    grp=getgrnam(name);
    if(grp==NULL)
        return -1;
    return grp->gr_gid;
}

int main(int argc,char* argv[]){
    //从密码文件中逐行读取密码
    struct passwd *pwd;
    while((pwd=getpwent())!=NULL)
        printf("%-8s %5ld\n",pwd->pw_name,(long)pwd->pw_uid);
    endpwent();
}