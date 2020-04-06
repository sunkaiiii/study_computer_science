#include<api.h>

unsigned long global_count;
int stopflag;

unsigned long __thread *counter;
DEFINE_PER_THREAD(unsigned long,counter)

void inc_count(void)
{
    ACCESS_ONCE(__get_thread_var(counter))++;   
}

unsigned long read_count(void)
{
    return ACCESS_ONCE(global_count);
}

void *eventual(void *arg)
{
    int t;
    int sum;

    while(stopflag<3)
    {
        sum = 0;
        for_each_thread(t)
            sum+=ACCESS_ONCE(per_thread(counter,t));

       ACCESS_ONCE(global_count)=sum;
       poll(NULL,0,1);
       if(stopflag)
       {
           smp_mb();
           stopflag++;
       } 
    }
    return NULL;
}

void count_init(void)
{
    thread_id_t tid;

    if(pthread_create(&tid,NULL,eventual,NULL))
    {
        perror("count_init:pthread_create");
        exit(-1);
    }
}

void count_cleanup(void)
{
    stopflag=1;
    while(stopflag<3)
    {
        poll(NULL,0,1);
        smp_mb();
    }
}