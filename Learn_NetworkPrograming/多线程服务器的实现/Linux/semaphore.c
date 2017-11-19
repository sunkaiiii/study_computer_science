#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>

//一个控制访问顺序的同步程序，使用信号量
//线程A从用户输入得到值后存入全局变量num，线程B取走该值并累加。
//该操作进行5次，完成后输出综合并退出程序

void *read(void *arg);
void *accu(void *arg);
static sem_t sem_one;
static sem_t sem_two;
static int num;

int main(int argc,char *argv[])
{
    pthread_t id_t1,id_t2;
    sem_init(&sem_one,0,0); //只允许一个线程访问信号量，并且初始值为0
    sem_init(&sem_two,0,1); //只允许一个线程访问信号量，并且初始值为1

    pthread_create(&id_t1,NULL,read,NULL);
    pthread_create(&id_t2,NULL,accu,NULL);

    pthread_join(id_t1,NULL);
    pthread_join(id_t2,NULL);

    sem_destroy(&sem_one);
    sem_destroy(&sem_two);
    return 0;
}

void *read(void *arg)
{
    int i;
    for(i=0;i<5;i++)
    {
        fputs("Input num: ",stdout);
        sem_wait(&sem_two); //读取一个数字
        scanf("%d",&num);
        sem_post(&sem_one); //通知accu线程，已经取到了一个数字，可以进行计算了
    }
    return NULL;
}

void *accu(void *arg)
{
    int sum=0;
    for(int i=0;i<5;i++)
    {
        sem_wait(&sem_one); //等待一个数字
        sum+=num;
        sem_post(&sem_two);

    }
    printf("Result:%d\n",sum);
    return NULL;
}
