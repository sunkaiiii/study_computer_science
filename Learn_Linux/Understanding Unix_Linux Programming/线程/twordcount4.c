/*
一种更进一步的多线程处理方法
展示了进程间的互通消息
*/

#include<stdio.h>
#include<pthread.h>
#include<ctype.h>

struct arg_set
{
  char *fname;
  int count;
};


struct arg_set *malibox;
pthread_mutex_t lock=PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t flag=PTHREAD_COND_INITIALIZER;

main(int ac,char *av[])
{
  pthread_t t1,t2;
  struct arg_set args1,args2;
  void *count_words(void*);
  int reports_in=0;
  int total_words=0;
  if(ac!=3)
  {
    printf("usage: %S file1 file2\n",av[0]);
    exit(1);
  }
  pthread_mutex_lock(&lock);  //给这个邮箱上锁
  args1.fname=av[1];
  args1.count=0;
  args2.fname=av[2];
  args2.count=0;
  pthread_create(&t1,NULL,count_words,(void*)&args1);
  pthread_create(&t2,NULL,count_words,(void*)&args2);
  while(reports_in<2)
  {
    printf("MAIN: waiting for flag to go up\n");
    /*
    *调用pthread_cond_wait之前，互斥锁lock已经定要锁上，否则，函数执行的效果将是未知的
    */
    pthread_cond_wait(&flag,&lock); //等待某个线程完成，此操作会释放指定的锁，完成后会将锁重新锁住
    printf("MAIN:Wow! flag was raised ,i have the lock\n");
    printf("%7d: %s\n",malibox->count,malibox->fname);
    total_words+=malibox->count;
    if(malibox==&args1)
      pthread_join(t1,NULL);
    if(malibox==&args2)
      pthread_join(t2,NULL);
    malibox=NULL;
    pthread_cond_signal(&flag);//操作完成，flag置为可用
    reports_in++;
  }
  printf("%7d: total words\n",total_words);
}
void *count_words(void *f)
{
  struct arg_set *args=f;
  FILE *fp;
  int c,prevc='\0';
  if((fp=fopen(args->fname,"r"))!=NULL)
  {
    while((c=getc(fp))!=EOF)
    {
      if(!isalnum(c)&&isalnum(prevc))
        args->count++;
      prevc=c;
    }
    fclose(fp);
  }
  else
    perror(args->fname);
  printf("COUNT: waiting to get lock\n");
  pthread_mutex_lock(&lock);  //获得当前的锁
  printf("COUNT:have lock,storing data\n");
  if(malibox!=NULL) //如果当前mailbox不为空，则main函数线程正在处理mailbox，释放锁，然后线程阻塞等待，完成后重新上锁
    pthread_cond_wait(&flag,&lock);
  malibox=args; //将当前指针放入信箱中
  printf("COUNT:raising flag\n");
  pthread_cond_signal(&flag);
  printf("COUNT:unlocking box\n");
  pthread_mutex_unlock(&lock); //释放锁
  return NULL;
}
