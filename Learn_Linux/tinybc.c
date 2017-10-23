/*
简单的bc实现
使用额两个管道，并创建一个进程来运行dc
在创建新的进程中，重定向标准输入和标准输出管道，然后运行exec dc
在父进程中，读取并分析用户的输入，将命令传给dc，dc读取响应，并把响应传给用户
*/
#include<stdio.h>

#define oops(m,x){perror(m);exit(x);}

main()
{
  int pid,todc[2],fromdc[2];
  //创建两个管道
  if(pipe(todc)==-1||pipe(fromdc)==-1
)
    oops("pipe failed",1);

  if((pid=fork())==-1)
    oops("cannot fork",2);
  if(pid==0)  //子进程运行dc
    be_dc(todc,fromdc);
  else  //父进程是ui，等待子进程结束
  {
      be_bc(todc,fromdc);
      wait(NULL);
  }

}
be_dc(int in[2],int out[2])
{
    //重定向标准输入和输出，然后执行dc
    if(dup2(in[0],0)==-1)
      oops("dc:cannot redirect stdin",3);
    close(in[0]); //已由dup接管至标准输入，从bc管道的内容读入数据到标准输入，调用dc
    close(in[1]); //不需要写入
    if(dup(out[1],1)==-1)
      oops("dc:cannot redirect stdout",4);
    //将dc计算后的标准输出绑定到输出管道到的write端
    close(out[1]);
    close(out[2]);

    execlp("dc","dc","-",NULL);
    oops("Cannot run dc",5);
}

be_bc(int todc[2],int fromdc[2])
{
  int num1,num2;
  char operation[BUFSIZ],message[BUFSIZ],*fgets();
  FILE *fpout,*fpin,*fdopen();
  close(todc[0]);
  close(fromdc[1]);
  //fdopen系统调用的作用是让文件描述符像文件一样的数用，第一个参数并非文件而是文件描述符
  fpout=fdopen(todc[1],"w");
  fpin=fdopen(fromdc[0],"r");
  if(fpout==NULL||fpin==NULL)
    fatal("Error convering pipes to streams");

  while(printf("tinybc:"),fgets(message,BUFSIZ,stdin)!=NULL)
  {
    if(sscanf(message,"%d%[-+*/^]%d",&num1,operation,&num2)!=3)
    {
      printf("syntax error \n");
      continue;
    }
    if(fprintf(fpout,"%d\n%d\n%c\np\n",num1,num2,*operation)==EOF)
      fatal("Error writing");
    fflush(fpout);
    if(fgets(message,BUFSIZ,fpin)==NULL)
      break;
    printf("%d %c %d= %s",num1,*operation,num2,message );
  }
  fclose(fpout);
  fclose(fpin);
}

fatal(char *mess[])
{
  fprintf(stderr,"error:%s\n",mess);
  exit(1);
}
