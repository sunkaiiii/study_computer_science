/*
[编程题] 消除重复元素
时间限制：1秒
空间限制：32768K
小易有一个长度为n序列，小易想移除掉里面的重复元素，但是小易想是对于每种元素保留最后出现的那个。小易遇到了困难,希望你来帮助他。 
输入描述:
输入包括两行：
第一行为序列长度n(1 ≤ n ≤ 50)
第二行为n个数sequence[i](1 ≤ sequence[i] ≤ 1000)，以空格分隔


输出描述:
输出消除重复元素之后的序列，以空格分隔，行末无空格

输入例子1:
9
100 100 100 99 99 99 100 100 100

输出例子1:
99 100
*/
#include<iostream>
#include<algorithm>
#include<string.h>
#include<vector>
#include<math.h>
using namespace std;
int main()
{
	int n;
	cin>>n;
	int a[52];
	for(int i=0;i<n;i++)
	{
		cin>>a[i];
	}
	int b[1002];
	memset(b,-1,sizeof(b));
	for(int i=0;i<n;i++)
	{
		b[a[i]]=i;
	}
	int c[52];
	int count=0;
	for(int i=0;i<1002;i++)
	{
		int min=b[i];
		int index=i;
		for(int i2=i;i2<1002;i2++)
		{
			if(min>b[i2])
			{
				min=b[i2];
				index=i2;
			}
		}
		int d=b[i];
		b[i]=min;
		b[index]=d;
	}
	for(int i=0;i<1002;i++)
	{
		cout<<b[i]<<endl;
		if(b[i]==-1)
			continue;
		c[count]=a[b[i]];
		count++;
	}
	for(int i=0;i<count;i++)
	{
		cout<<c[i];
		if(i<count-1)
			cout<<' ';
	}
}
