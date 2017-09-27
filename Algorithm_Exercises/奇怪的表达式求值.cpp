/*
[编程题] 奇怪的表达式求值
时间限制：1秒
空间限制：32768K
常规的表达式求值，我们都会根据计算的优先级来计算。比如*的优先级就高于+-。但是小易所生活的世界的表达式规则很简单，从左往右依次计算即可，而且小易所在的世界没有除法，意味着表达式中没有/，只有(+, - 和 *)。现在给出一个表达式，需要你帮忙计算出小易所在的世界这个表达式的值为多少 
输入描述:
输入为一行字符串，即一个表达式。其中运算符只有-,+,*。参与计算的数字只有0~9.
保证表达式都是合法的，排列规则如样例所示。


输出描述:
输出一个数，即表达式的值

输入例子1:
3+5*7

输出例子1:
56
*/
#include<iostream>
#include<algorithm>
#include<string.h>
#include<vector>
#include<math.h>
#include<map>
#include<queue>
int main()
{
	char a[100000];
	std::cin>>a;
	std::queue<char> q;
	for(int i=0;i<strlen(a);i++)
	{
		q.push(a[i]);
	}
	int result=0;
	int first=1;
	int d=0;
	int e=0;
	char signal;
	while(!q.empty())
	{
		if(q.front()>='0'&&q.front()<='9')
		{
			int p=q.front();
			q.pop();
			d=d*10+(p-'0');
		}
		else
		{
			if(first)
			{
				result+=d;
				first=0;
				continue;
			}
			signal=q.front();
			q.pop();
			e=0;
			while(!q.empty())
			{
				if(q.front()>='0'&&q.front()<='9')
				{
					int p2=q.front();
					q.pop();
					e=e*10+(p2-'0');
				}
				else
				{
					if(signal=='+')
					{
						result+=e;
					}
					else if(signal=='-')
					{
						result-=e;
					}
					else if(signal=='*')
					{
						result*=e;
					}
					break;
				}
			}
		}
	}
	if(signal=='+')
	{
		result+=e;
	}
	else if(signal=='-')
	{
		result-=e;
	}
	else if(signal=='*')
	{
		result*=e;
	}
	std::cout<<result<<std::endl;
} 
