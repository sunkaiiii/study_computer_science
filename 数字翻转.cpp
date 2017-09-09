/*
题目描述
对于一个整数X，定义操作rev(X)为将X按数位翻转过来，并且去除掉前导0。例如:
如果 X = 123，则rev(X) = 321;
如果 X = 100，则rev(X) = 1.
现在给出整数x和y,要求rev(rev(x) + rev(y))为多少？
输入描述:
输入为一行，x、y(1 ≤ x、y ≤ 1000)，以空格隔开。
输出描述:
输出rev(rev(x) + rev(y))的值
示例1
输入

123 100
输出

223
*/
#include<iostream>
int main()
{
	int x,y;
	std::cin>>x>>y;
	int x2=0,y2=0;
	while(x>0)
	{
		x2=x2*10+x%10;
		x/=10;
	}
	while(y>0)
	{
		y2=y2*10+y%10;
		y/=10;
	}
	int add=x2+y2;
	int result=0;
	while(add>0)
	{
		result=result*10+add%10;
		add/=10;
	}
	std::cout<<result<<std::endl;
}
