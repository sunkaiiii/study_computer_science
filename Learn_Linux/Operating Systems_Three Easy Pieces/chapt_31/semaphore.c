//semaphore.c -- 一个基于信号量的生产者消费者
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#define MAX 15
sem_t empty;
sem_t full;
sem_t mutex;
const int loops=10;
int buffer[MAX];
int fill=0;
int use=0;
void put(int value)
{
    buffer[fill]=value;
    fill=(fill+1)%MAX;
}

int get()
{
    int temp=buffer[use];
    use=(use+1)%MAX;
    return temp;
}

void *producer(void *arg)
{
    int i;
    for(i=0;i<loops;i++)
    {
        sem_wait(&empty);
        sem_wait(&mutex);
        put(i);
        sem_post(&mutex);
        sem_post(&full);
    }
}

void *consumer(void *arg)
{
    int i;
    for(i=0;i<loops;i++)
    {
        sem_wait(&full);
        sem_wait(&mutex);
        int temp=get();
        sem_post(&mutex);
        sem_post(&empty);
        printf("%d\n",temp);
    }
}

int main()
{
    sem_init(&empty,0,MAX);
    sem_init(&full,0,0);
    sem_init(&mutex,0,1);
    /*
    starting producer and consumer
    ....
    */
}