/*
Fibonacci数列是这样定义的：
F[0] = 0
F[1] = 1
for each i ≥ 2: F[i] = F[i-1] + F[i-2]
因此，Fibonacci数列就形如：0, 1, 1, 2, 3, 5, 8, 13, ...，在Fibonacci数列中的数我们称为Fibonacci数。给你一个N，你想让其变为一个Fibonacci数，每一步你可以把当前数字X变为X-1或者X+1，现在给你一个数N求最少需要多少步可以变为Fibonacci数。
输入描述:
输入为一个正整数N(1 ≤ N ≤ 1,000,000)
输出描述:
输出一个最小的步数变为Fibonacci数"
示例1
输入

15
输出

2
*/
#include<cstring>
#include<iostream>
#include<algorithm>
#include<cmath>
int result=0;
int main()
{
	int count=2;
	int a[99999];
	a[0]=0;
	a[1]=1;
	do
	{
		a[count]=a[count-2]+a[count-1];
	}while(a[count++]<=1000000);
	int n;
	std::cin>>n;
	for(int i=0;i<count;i++)
	{
		if(a[i]==n)
		{
			std::cout<<0<<std::endl;
			return 0;
		}
		if(a[i]>n)
		{
			int a1=n-a[i-1];
			int a2=a[i]-n;
			result=a1<a2?a1:a2; 
			std::cout<<result<<std::endl;
			return 0;
		}
	}
}
