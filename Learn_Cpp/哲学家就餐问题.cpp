#include<stdio.h>
#define N 5
#define LEFT (i+N-1)%N
#define RIGHT (i+1)%N
#define THINKING 0
#define HUNGRY 1
#define EATING 2
#define TRUE 1
typedef int semaphore;
int state[N];
semaphore mutex=1;
semaphore s[N];

void down(semaphore *mutex)
{
  mutex--;
}
void up(semaphore *mutex)
{
  mutex++;
}
void test(int i)
{
  if(state[i]==HUNGRY&&state[LEFT]!=EATING&&state[RIGHT]!=EATING)
  {
    state[i]=EATING;
    up(&s[i]);
  }
}
void philosopher(int i)
{
  while(TRUE){}
}
void take_forks(int i)
{
  down(&mutex);
  state[i]=HUNGRY;
  test(i);
  up(&mutex);
  down(&s[i]);
}
void put_forks(int i)
{
  down(&mutex);
  state[i]=THINKING;
  test(LEFT);
  test(RIGHT);
  up(&mutex);
}
int main()
{
  
}
