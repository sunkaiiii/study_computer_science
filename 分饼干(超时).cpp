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
int b[20];
int length;
int count = 0;
int n;
int result=0;
void f(int a2,int n2)
{
	if(n2==length)
	{
		if(a2%n==0)
		{
			result++;
		}
	}
	else
	{
		if(b[n2]==1)
		{
			for(int i=0;i<10;i++)
			{
				a2=a2*10+i;
				f(a2,n2+1);
				a2=a2/10;
			}
		}
		else
		{
			a2=a2*10+a[n2]-'0';
			f(a2,n2+1);
		}
	}
}
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
	f(0,0);
	//std::cout << a2 << std::endl;
	std::cout<<result<<std::endl;
}
