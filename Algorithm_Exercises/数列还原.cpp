/*
题目描述
牛牛的作业薄上有一个长度为 n 的排列 A，这个排列包含了从1到n的n个数，但是因为一些原因，其中有一些位置（不超过 10 个）看不清了，但是牛牛记得这个数列顺序对的数量是 k，顺序对是指满足 i < j 且 A[i] < A[j] 的对数，请帮助牛牛计算出，符合这个要求的合法排列的数目。
输入描述:
每个输入包含一个测试用例。每个测试用例的第一行包含两个整数 n 和 k（1 <= n <= 100, 0 <= k <= 1000000000），接下来的 1 行，包含 n 个数字表示排列 A，其中等于0的项表示看不清的位置（不超过 10 个）。
输出描述:
输出一行表示合法的排列数目。
示例1
输入

5 5
4 0 0 2 0
输出

2
*/
#include<iostream>
#include<cmath>
#include<string.h>
#include<algorithm>
int result=0;
int n;
int a[102];
int c[52];
long k;
int count=0;
void judge(int b[]);
void f(int b[],int c)
{
	if(c==count)
	{
		int a2[102];
		memset(a2,0,sizeof(a2));
		int c2=0;
		for(int i=0;i<n;i++)
		{
			if(a[i]==0)
			{
				a2[i]=b[c2];
				c2++;
			}
			else
			{
				a2[i]=a[i];
			}
		}
		judge(a2);
	}
	else
	{
		for(int i=1;i<=n;i++)
		{
			int ok=1;
			for(int i2=0;i2<=c-1;i2++)
			{
				if(b[i2]==i)
				{
					ok=0;
				}
			}
			for(int i2=0;i2<n;i2++)
			{
				if(a[i2]!=0&&a[i2]==i)
				{
					ok=0;
				}
			}
			if(ok)
			{
				b[c]=i;
				f(b,c+1);
			}
		}
	}
}
void judge(int b[])
{
	int step=0;
	for(int i=0;i<n;i++)
	{
		for(int i2=i+1;i2<n;i2++)
		{
			if(b[i]<b[i2])
			{
				step++;
			}
			if(step>k)
				return;
		}
		//std::cout<<b[i];
	}
	//std::cout<<std::endl<<step<<std::endl;
	if(step==k)
	{
		result++;
	}
}
int main()
{
	std::cin>>n>>k;
	int b[n];
	memset(b,0,sizeof(b));
	for(int i=0;i<n;i++)
	{
		std::cin>>a[i];
		if(a[i]==0)
		{
			count++;
		}
	}
	f(b,0);
	std::cout<<result<<std::endl;
}
