#include<stdio.h>
#include<arpa/inet.h>

/*
展示inet_addr的作用
即将点分十进制表示法转换为整数表示法
*/
int main(int argc,char *argv[])
{
  char *addr1="1.2.3.4";
  char *addr2="1.2.3.256";

  unsigned long conv_addr=inet_addr(addr1);
  if(conv_addr==INADDR_NONE)
    printf("Error occured \n");
  else
    printf("Network ordered integer addr : %#lx\n",conv_addr);

  conv_addr=inet_addr(addr2);
  if(conv_addr==INADDR_NONE)
    printf("Error occured \n");
  else
    printf("Network ordered integer addr : %#lx\n",conv_addr);
}
