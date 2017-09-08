/*
神奇数
时间限制：1秒
空间限制：32768K
题目描述
东东在一本古籍上看到有一种神奇数,如果能够将一个数的数字分成两组,其中一组数字的和等于另一组数字的和,我们就将这个数称为神奇数。例如242就是一个神奇数,我们能够将这个数的数字分成两组,分别是{2,2}以及{4},而且这两组数的和都是4.东东现在需要统计给定区间中有多少个神奇数,即给定区间[l, r],统计这个区间中有多少个神奇数,请你来帮助他。
输入描述:
输入包括一行,一行中两个整数l和r(1 ≤ l, r ≤ 10^9, 0 ≤ r - l ≤ 10^6),以空格分割
输出描述:
输出一个整数,即区间内的神奇数个数
示例1
输入
1 50
输出
4
*/
#include<iostream>
#include<cmath>
int N=10;
int result=0;
int ok=0;
int single=0;
  int l,r;
void judge(int a[10],int add,int second_add,int single)
{
  if(ok)
  {
    return;
  }
  if(add<second_add)
  {
    return;
  }
  if(add==second_add)
  {
    ok=1;
    result++;
    std::cout<<l<<std::endl;
    return;
  }
  if(single=0)
  {
    for(int i=9;i>=0;i--)
    {
      if(ok)
      {
        return;
      }
      if(a[i]>0&&(add-i>=second_add+i))
      {
        a[i]--;
        add-=i;
        second_add+=i;
        judge(a,add,second_add,1);
        a[i]++;
        add+=i;
        second_add-=i;
      }
    }
  }
  else
  {
    for(int i=0;i<10;i++)
    {
      if(ok)
      {
        return;
      }
      if(a[i]>0&&(add-i>=second_add+i))
      {
        a[i]--;
        add-=i;
        second_add+=i;
        judge(a,add,second_add,0);
        a[i]++;
        add+=i;
        second_add-=i;
      }
    }
  }
}
void f(int a)
{
  int k[10];
  int add=0;
  for(int i=0;i<10;i++)
  {
    k[i]=0;
  }
  while(a>0)
  {
    k[a%10]++;
    add+=a%10;
    a/=10;
  }
  judge(k,add,0,0);
}
int main()
{
  std::cin>>l>>r;
  for(l=10;l<=r;l++)
  {
    ok=0;
    f(l);
  }
  std::cout<<result<<std::endl;
}
