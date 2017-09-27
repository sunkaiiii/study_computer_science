/*
集合
时间限制：1秒
空间限制：32768K
给你两个集合，要求{A} + {B}。 注：同一个集合中不会有两个相同的元素。
输入描述:
每组输入数据分为三行,第一行有两个数字n,m(0 ≤ n,m ≤ 10000)，分别表示集合A和集合B的元素个数。后两行分别表示集合A和集合B。每个元素为不超过int范围的整数,每个元素之间有个空格隔开。


输出描述:
针对每组数据输出一行数据，表示合并后的集合，要求从小到大输出，每个元素之间有一个空格隔开,行末无空格。

输入例子1:
3 3
1 3 5
2 4 6

输出例子1:
1 2 3 4 5 6
*/
#include<iostream>
#include<algorithm>
#include<map>
int main()
{
  int n1,n2;
  std::cin>>n1>>n2;
  int a[n1+1];
  int b[n2+1];
  std::map<int,int> m;
  std::map<int, int>::iterator it;
  std::map<int,int>::iterator it2;
  for(int i=0;i<n1;i++)
  {
    std::cin>>a[i];
    if(m.find(a[i])==m.end())
    {
      m[a[i]]=1;
    }
  }
  for(int i=0;i<n2;i++)
  {
    std::cin>>b[i];
    if(m.find(b[i])==m.end())
    {
      m[b[i]]=1;
    }
  }
  for(it=m.begin();it!=m.end();it++)
  {
    std::cout<<it->first;
    it++;
    if(it!=m.end())
      std::cout<<" ";
    it--;
  }
}
