/*
 度度熊回家
时间限制：1秒
空间限制：32768K
一个数轴上共有N个点，第一个点的坐标是度度熊现在位置，第N-1个点是度度熊的家。现在他需要依次的从0号坐标走到N-1号坐标。
但是除了0号坐标和N-1号坐标，他可以在其余的N-2个坐标中选出一个点，并直接将这个点忽略掉，问度度熊回家至少走多少距离？ 
输入描述:
输入一个正整数N, N <= 50。

接下来N个整数表示坐标，正数表示X轴的正方向，负数表示X轴的负方向。绝对值小于等于100


输出描述:
输出一个整数表示度度熊最少需要走的距离。

输入例子1:
4
1 4 -1 3

输出例子1:
4
*/
#include<cstring>
#include<iostream>
#include<algorithm>
#include<cmath> 
int main()
{
	int n;
	std::cin>>n;
	int a[n+2];
	for(int i=0;i<n;i++)
	{
		std::cin>>a[i];
	}
    int result=100000;
	for(int i=1;i<n-1;i++)
	{
		int try2=0;
		for(int j=1;j<n;j++)
		{
			if(j==i)
				continue;
			if(j-1==i)
			{
				try2+=fabs(a[j]-a[j-2]);
			}
			else
			{
				try2+=fabs(a[j]-a[j-1]);
			}
		}
		if(try2<result)
			result=try2;
	}
    std::cout<<result<<std::endl;
}