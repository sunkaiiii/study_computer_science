/*
[编程|20分] 操作序列
时间限制：1秒
空间限制：32768K
题目描述
小易有一个长度为n的整数序列,a_1,...,a_n。然后考虑在一个空序列b上进行n次以下操作:
1、将a_i放入b序列的末尾
2、逆置b序列
小易需要你计算输出操作n次之后的b序列。
输入描述:
输入包括两行,第一行包括一个整数n(2 ≤ n ≤ 2*10^5),即序列的长度。
第二行包括n个整数a_i(1 ≤ a_i ≤ 10^9),即序列a中的每个整数,以空格分割。
输出描述:
在一行中输出操作n次之后的b序列,以空格分割,行末无空格。
示例1
输入

4
1 2 3 4
输出

4 2 1 3
*/
#include<iostream>
#include<list>
int main()
{
	long n;
	std::cin>>n;
	std::list<long> a;
	int ok=0;
	for(long i=0;i<n;i++)
	{
		long c;
		std::cin>>c;
		if(ok%2==0)
			a.push_back(c);
		else
			a.push_front(c);
		ok=(ok+1)%2;
	}
	std::list<long>::iterator it;
	if(ok%2==0)
	{
		for(it=a.begin();it!=a.end();) 
		{
			std::cout<<*it;
			it++;
			if(it!=a.end())
			{
				std::cout<<' ';
			}
		}
	}
	else
	{
		for(it=a.end();;)
		{
			if(it==a.end())
			{
				it--;
				continue;
			}
			std::cout<<*it;
			if(it!=a.begin())
			{
				std::cout<<' ';
			}
			else
			{
				std::cout;
				break;
			}
			it--;
		}
	}
}
