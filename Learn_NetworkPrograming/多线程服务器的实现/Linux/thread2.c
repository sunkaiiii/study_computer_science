#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include<string.h>
#include <stdlib.h>

//一个调用pthread_join并且获得线程返回值的用例
void *thread_main(void *arg);

int main(int argc,char *argv[])
{
    pthread_t t_id;
    int thread_param=5;
    void *thr_ret;

    if(pthread_create(&t_id,NULL,thread_main,(void*)&thread_param)!=0)
    {
        puts("pthread_create() error");
        return -1;
    }
    if(pthread_join(t_id,&thr_ret)!=0)
    {
        puts("pthread_join() error");
        return -1;
    }
    printf("Thread return message:%s\n",(char*)thr_ret);
    free(thr_ret); //因为这个消息是malloc的，所以要注意删除
    return 0;
}

void *thread_main(void *arg)
{
    int i;
    int cnt=*((int*)arg);
    char *msg=(char*)malloc(sizeof(char)*50); //如果不是用动态申请，线程独立的栈空间会在运行结束之后销毁
    strcpy(msg,"Hello,i am thread\n");
    for(i=0;i<cnt;i++)
    {
        sleep(1);
        puts("running thread");
    }
    return (void*)msg;
}
