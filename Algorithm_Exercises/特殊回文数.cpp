/*问题描述
　　123321是一个非常特殊的数，它从左边读和从右边读是一样的。
　　输入一个正整数n， 编程求所有这样的五位和六位十进制数，满足各位数字之和等于n 。
输入格式
　　输入一行，包含一个正整数n。
输出格式
　　按从小到大的顺序输出满足条件的整数，每个整数占一行。
*/
#include<iostream>
#include<cstring> 
using namespace std;
int a[100000];
int main()
{
	int b, c=0, d=10000,e;
	cin >> b;
	while (d <= 999999)
	{
		int k = d;
		int j= 0;
		e=0;
		while (k > 0)
		{
			j = k % 10 + j*10;
			e=k%10+e;
			k /= 10;
		}
		if (d == j&&e==b)
		{
			cout<<d<<endl;
		}
		d++; 
	}
}
