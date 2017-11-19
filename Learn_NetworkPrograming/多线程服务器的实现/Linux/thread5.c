#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<pthread.h>
#define NUM_THREAD 100

void *thread_inc(void *arg);
void *thread_des(void *arg);

long long num=0;
pthread_mutex_t mutex;

//互斥量的使用，解决thread4.c中遇到的问题

int main(int argc,char *argv[])
{
    pthread_t thread_id[NUM_THREAD];
    int i;
    pthread_mutex_init(&mutex,NULL);

    printf("sizeof long long :%d\n", sizeof(long long));
    for(i=0;i<NUM_THREAD;++i)
    {
        if(i%2)
            pthread_create(&(thread_id[i]),NULL,thread_inc,NULL);
        else
            pthread_create(&(thread_id[i]),NULL,thread_des,NULL);
    }
    for(i=0;i<NUM_THREAD;++i)
    {
        pthread_join(thread_id[i],NULL);
    }
    printf("result:%ld\n",num);
    pthread_mutex_destroy(&mutex);
    return 0;
}

void *thread_inc(void *arg)
{
    int i;
    pthread_mutex_lock(&mutex); //为临界区上锁
    for(i=0;i<50000000;++i)
        num+=1;
    pthread_mutex_unlock(&mutex); //不要忘记解锁
    return NULL;
}

void *thread_des(void *arg)
{
    int i;
    pthread_mutex_lock(&mutex); //为临界区上锁
    for(i=0;i<50000000;++i)
        num-=1;
    pthread_mutex_unlock(&mutex); //不要忘记解锁
    return NULL;
}
