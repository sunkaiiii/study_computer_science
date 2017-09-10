/*
奇异数
时间限制：1秒
空间限制：32768K
题目描述
如果一个数字满足以下条件,我们就称它为奇异数:
1、这个数字至少有两位
2、这个数的最低两位是相同的
比如: 1488是一个奇异数,而3、112不是。
牛牛现在给出一个一个区间[L,R],让你计算出在区间内有多少个奇异数
输入描述:
输入包括两个正整数L和R(1 ≤ L ≤ R ≤ 10^12),以空格分割。
输出描述:
输出一个正整数,即区间内的奇异数的个数。
示例1
输入

10 20
输出

1
*/
#include<iostream>
#include<cmath>
long long result=0;
long long cal(long long left,long long right)
{
  long long sub=right-left;
  while(sub>=100)
  {
    result+=10;
    sub-=100;
  }
  for(int i=0;i<=sub;i++)
  {
    long long j=left;
    int c=j%10;
    j/=10;
    if(j%10==c)
    {
      result++;
    }
    left++;
  }
  return result;
}
int main()
{
  long long n,m;
  std::cin>>n>>m;
  std::cout<<cal(n,m)<<std::endl;
}
