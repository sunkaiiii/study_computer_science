/*
[编程题] 双核处理
时间限制：1秒
空间限制：32768K
一种双核CPU的两个核能够同时的处理任务，现在有n个已知数据量的任务需要交给CPU处理，假设已知CPU的每个核1秒可以处理1kb，每个核同时只能处理一项任务。n个任务可以按照任意顺序放入CPU进行处理，现在需要设计一个方案让CPU处理完这批任务所需的时间最少，求这个最小的时间。 
输入描述:
输入包括两行：
第一行为整数n(1 ≤ n ≤ 50)
第二行为n个整数length[i](1024 ≤ length[i] ≤ 4194304)，表示每个任务的长度为length[i]kb，每个数均为1024的倍数。


输出描述:
输出一个整数，表示最少需要处理的时间

输入例子1:
5
3072 3072 7168 3072 1024

输出例子1:
9216
*/
#include<iostream>
#include<algorithm>
using namespace std;
int b[52];
int result=0;
void f(int sum1,int sum2,int i)
{
	//cout<<sum1<<","<<sum2<<endl;
	if(i<0)
		return;
	if(sum1-b[i]>sum2)
	{
		sum1-=b[i];
		sum2+=b[i];
		f(sum1,sum2,i-1);
		sum1+=b[i];
		sum2-=b[i];
		f(sum1,sum2,i-1);
	}
	else
	{
		if(result==0)
		{
			result=sum2+b[i];
			return;
		}
		else
		{
			if(sum1>sum2)
			{
				if(result>sum1)
					result=sum1;
			}
			else
			{
				if(result>sum2)
					result=sum2;
			}		
		} 
		return;
	}
}
int main()
{
	int a;
	int sum=0;
	cin>>a;
	for(int i=0;i<a;i++)
	{
		cin>>b[i];
		sum+=b[i];
	}
	sort(b,b+a);
	int sum2=0;
	f(sum,sum2,a-1);
	cout<<result<<endl;
}
