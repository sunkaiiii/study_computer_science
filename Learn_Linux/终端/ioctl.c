/*
测试ioctl的用法，显示终端屏幕的尺寸
*/
#include<sys/ioctl.h>
int main()
{
  struct winsize wbuf;
  if(ioctl(0,TIOCGWINSZ,&wbuf)!=-1)
  {
    printf("%d row x %s cols\n",wbuf.ws_row,wbuf.ws_col);
    printf("%d wide x %d tall \n",wbuf.ws_xpixel,wbuf.ws_ypixel);
  }
}
