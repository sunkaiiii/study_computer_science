/*
寻找丑数
时间限制：1秒
空间限制：65536K
题目描述
把只包含因子2、3和5的数称作丑数（Ugly Number）。例如6、8都是丑数，但14不是，因为它包含因子7。 习惯上我们把1当做是第一个丑数。求按从小到大的顺序的第N个丑数。
输入描述:
整数N
输出描述:
第N个丑数
*/
#include<iostream>
int result=0;
void judge(int a)
{
	while(a%2==0)
	{
		a/=2;
	}
	while(a%3==0)
	{
		a/=3;
	}
	while(a%5==0)
	{
		a/=5;
	}
	if(a==1)
	{
		result++;
	}
	else
	{
		return;
	}
}
int main()
{
	int n;
	std::cin>>n;
	for(int i=1;;i++)
	{
		judge(i);
		if(n==result)
		{
			std::cout<<i<<std::endl;
			break;
		}
	}
}
