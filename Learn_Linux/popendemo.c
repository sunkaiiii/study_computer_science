/*
以who|sort作为数据源，通过popen来获得当前用户排序列表
popen打开shell命令，使他可以看似文件一样的操作
*/

#include<stdio.h>
#include<stdlib.h>

int main()
{
  FILE *fp;
  char buf[100];
  int i=0;

  fp=popen("who|sort","r"); //打开一个命令

  while(fgets(buf,100,fp)!=NULL) //从命令中读取
  {
    printf("%3d %s",i++,buf); //打印数据
  }
  pclose(fp); //千万不要忘记关闭连接
  return 0;
}
