/*
题目描述
小易有一个圆心在坐标原点的圆，小易知道圆的半径的平方。小易认为在圆上的点而且横纵坐标都是整数的点是优雅的，小易现在想寻找一个算法计算出优雅的点的个数，请你来帮帮他。
例如：半径的平方如果为25
优雅的点就有：(+/-3, +/-4), (+/-4, +/-3), (0, +/-5) (+/-5, 0)，一共12个点。
输入描述:
输入为一个整数，即为圆半径的平方,范围在32位int范围内。
输出描述:
输出为一个整数，即为优雅的点的个数
示例1
输入

25
输出

12
*/
#include<iostream>
#include<cmath>
int main()
{
  int n;
  std::cin>>n;
  int r=sqrt(n);
  int start=0;
  if(r*r==n)
  {
    start=1;
    r--;
  }
  int result=0;
  for(int i=1;i<=r;i++)
  {
    int b=sqrt(n-i*i);
    if(b*b+i*i==n)
    {
      result++;
    }
  }
  result*=4;
  if(start)
    result+=4;
  std::cout<<result<<std::endl;
}
