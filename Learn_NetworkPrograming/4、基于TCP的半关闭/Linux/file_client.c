#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>

#define BUF_SIZE 30

void error_handling(char *message);

//接受文件的客户端，省略了一些错误判断
int main(int argc,char *argv[])
{
  if(argc!=3)
  {
    printf("Usage:%s <ip> <port> \n",argv[0]);
    exit(1);
  }
  int sd;
  FILE *fp;

  char buf[BUF_SIZE];
  int read_cnt;
  struct sockaddr_in serv_adr;
  fp=fopen("receive.dat","wb");
  sd=socket(PF_INET,SOCK_STREAM,0);
  memset(&serv_adr,0,sizeof(serv_adr));
  serv_adr.sin_family=AF_INET;
  serv_adr.sin_addr.s_addr=inet_addr(argv[1]);
  serv_adr.sin_port=htons(atoi(argv[2]));;
  connect(sd,(struct sockaddr*)&serv_adr,sizeof(serv_adr));
  //从服务器读取传输而来的数据，并写入文件
  while((read_cnt=read(sd,buf,BUF_SIZE))!=0)
    fwrite((void*)buf,1,read_cnt,fp);
  //文件写入完成后向服务器发送确认信息，此时服务器半关闭了发送端，但是还可以接受信息
  puts("Received file data\n");
  write(sd,"Thank you",sizeof("Thank you"));
  fclose(fp);
  close(sd);
  return 0;
}

void error_handling(char *message)
{
  fputs(message,stderr);
  fputc('\n',stderr);
  exit(1);
}
