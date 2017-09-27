/*
问题描述
　　元旦快到了，校学生会让乐乐负责新年晚会的纪念品发放工作。为使得参加晚会的同学所获得的纪念品价值 相对均衡，他要把购来的纪念品根据价格进行分组，但每组最多只能包括两件纪念品，并且每组纪念品的价格之和不能超过一个给定的整数。为了保证在尽量短的时 间内发完所有纪念品，乐乐希望分组的数目最少。
　　你的任务是写一个程序，找出所有分组方案中分组数最少的一种，输出最少的分组数目。
输入格式
　　输入包含n+2行：
　　第1行包括一个整数w，为每组纪念品价格之和的上限。
　　第2行为一个整数n，表示购来的纪念品的总件数。
　　第3~n+2行每行包含一个正整数pi (5 <= pi <= w)，表示所对应纪念品的价格。
输出格式
　　输出仅一行，包含一个整数，即最少的分组数目。
样例输入
100
9
90
20
20
30
50
60
70
80
90
样例输出
6
数据规模和约定
　　50%的数据满足：1 <= n <= 15
　　100%的数据满足：1 <= n <= 30000, 80 <= w <= 200
*/
#include	<iostream>
#include <algorithm>
using namespace std;
int main()
{
	int edge;
	int n;
	int a[100000];
	int b[100000];
	cin>>edge>>n;
	for(int i=0;i<n;i++)
	{
		cin>>a[i];
		b[i]=1;
	}
	// for(int i=0;i<n;i++)
	// {
	// 	int min=i;
	// 	for(int i2=i+1;i2<n;i2++)
	// 	{
	// 		if(a[i2]<a[min])
	// 			min=i2;
	// 	}
	// 	int c=a[i];
	// 	a[i]=a[min];
	// 	a[min]=c;
	// }
	sort(a,a+n);
	int count=n-1;
	int ans=0;
	while(count>=0)
	{
		for(int i=count;i>=0;i--)
		{
			int ok=0;
			if(b[i]==1)
			{
				for(int i2=0;i2<i;i2++)
				{
					if(b[i2]==1&&b[i]==1&&ok==0)
					{
						if((a[i]+a[i2])<=edge)
						{
							count-=2;
							b[i]=0;
							b[i2]=0;
							ans++;
						}
						else
						{
							ok=1;
						}
					}
					else if(ok==1)
					{
						break;
					}
				}
			}
			if(b[i]==1)
			{
				count--;
				b[i]=0;
				ans++;
			}
		}
		//cout<<count<<",";
	}
	cout<<ans<<endl;
}
