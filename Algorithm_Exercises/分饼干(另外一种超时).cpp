/*
易老师购买了一盒饼干，盒子中一共有k块饼干，但是数字k有些数位变得模糊了，看不清楚数字具体是多少了。易老师需要你帮忙把这k块饼干平分给n个小朋友，易老师保证这盒饼干能平分给n个小朋友。现在你需要计算出k有多少种可能的数值 
输入描述:
输入包括两行：

第一行为盒子上的数值k，模糊的数位用X表示，长度小于18(可能有多个模糊的数位)

第二行为小朋友的人数n


输出描述:
输出k可能的数值种数，保证至少为1

输入例子1:
9999999999999X
3

输出例子1:
4
*/
#include<iostream>
#include<algorithm>
#include<string.h>
#include<cmath>
char a[20];
int jilu[500000];
int length; 
int n;
int b[20];
int result=0;
int main()
{
	std::cin >> a;
	length=strlen(a);
	std::cin >> n;
	memset(b, -1, sizeof(b));
	long long a2 = 0;
	for (int i=0; i<strlen(a); i++)
	{
		if (a[i]<'0' || a[i]>'9')
		{
			int c=strlen(a)-1;
			int index = fabs(i - c);
			//std::cout<<index<<std::endl;
			b[index] = 1;
			a2 = a2 * 10;		
		}
		else
		{
			a2 = a2 * 10 +( a[i] - '0');
		}
	}
	long long c=0;
	long long a3=a2;
	int count=0;
	while(a3>0)
	{
		if(b[count]==1)
		{
			c=c*10+9;		
		}
		else
		{
			c=c*10+a3%10;
		}
		a3/=10;
		count++;
	}
	long long d=c;
	c=0;
	while(d>0)
	{
		c=c*10+d%10;
		d/=10;
	}
	int step=1;
	for(long long i=a2;i<=c;i=i+step)
	{
		long long test=i;
		long long a222=a2;
		//std::cout<<i<<std::endl;
		if(i%n==0)
		{
			step=n;
			for(int t=0;t<strlen(a);t++)
			{
				if(b[t]!=1)
				{
					if(test%10!=a222%10)
					{
						break;
					}
				}
				if(t==strlen(a)-1)
				{
					//std::cout<<i<<std::endl;
					result++;
				}
				test/=10;
				a222/=10;
			}
		}
	}
	std::cout<<result<<std::endl;
}
