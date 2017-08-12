/*
题目描述
一个袋子里面有n个球，每个球上面都有一个号码(拥有相同号码的球是无区别的)。如果一个袋子是幸运的当且仅当所有球的号码的和大于所有球的号码的积。
例如：如果袋子里面的球的号码是{1, 1, 2, 3}，这个袋子就是幸运的，因为1 + 1 + 2 + 3 > 1 * 1 * 2 * 3
你可以适当从袋子里移除一些球(可以移除0个,但是别移除完)，要使移除后的袋子是幸运的。现在让你编程计算一下你可以获得的多少种不同的幸运的袋子。
输入描述:
第一行输入一个正整数n(n ≤ 1000)
第二行为n个数正整数xi(xi ≤ 1000)
输出描述:
输出可以产生的幸运的袋子数
示例1
输入

3
1 1 1
输出

2
*/
#include<iostream>
#include<cmath>
#include<string.h>
#include<algorithm>
int result=0;
long long sum=0;
long long cheng=1;
int n;
void f(int a[],int index)
{
	for(int i=index;i<n;i++)
	{
		std::cout<<index<<","<<i<<std::endl;
		sum+=a[i];
		cheng*=a[i];
		if(sum>cheng)
		{
			result++;
			f(a,i+1);
		}
		else if(a[i]==1)
		{
			f(a,index+1);
		}
		else
		{
			sum -= a[i];
            cheng /= a[i];
			break;
		}
		sum-=a[i];
		cheng/=a[i];
		for(;i<n-1&&a[i]==a[i+1];i++);
	}
}
int main()
{
	std::cin>>n;
	int a[n];
	for(int i=0;i<n;i++)
	{
		std::cin>>a[i];
	}
	std::sort(a,a+n);
	f(a,0);
	std::cout<<result<<std::endl;
}
