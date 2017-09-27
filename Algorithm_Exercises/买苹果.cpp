/*
题目描述
小易去附近的商店买苹果，奸诈的商贩使用了捆绑交易，只提供6个每袋和8个每袋的包装(包装不可拆分)。 可是小易现在只想购买恰好n个苹果，小易想购买尽量少的袋数方便携带。如果不能购买恰好n个苹果，小易将不会购买。
输入描述:
输入一个整数n，表示小易想购买n(1 ≤ n ≤ 100)个苹果
输出描述:
输出一个整数表示最少需要购买的袋数，如果不能买恰好n个苹果则输出-1
示例1
输入

20
输出

3
*/
#include<iostream>
long long result=0;
int main()
{
	int n;
	std::cin>>n;
	if(n%2==1)
	{
		std::cout<<-1<<std::endl;
		return 0;
	}
	else
	{
		for(int i=n/8;i>=0;i--)
		{
			for(int j=0;j<=n/6;j++)
			{
				if(i*8+j*6==n)
				{
					std::cout<<i+j<<std::endl;
					return 0;
				}
				else if(i*8+j*6>n)
				{
					break;
				}
			}
		}
	}
	std::cout<<-1<<std::endl;
}
