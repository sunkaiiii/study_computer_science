/*
奇数位丢弃
时间限制：1秒
空间限制：32768K
对于一个由0..n的所有数按升序组成的序列，我们要进行一些筛选，每次我们取当前所有数字中从小到大的第奇数位个的数，并将其丢弃。重复这一过程直到最后剩下一个数。请求出最后剩下的数字。

输入描述:
每组数据一行一个数字，为题目中的n(n小于等于1000)。


输出描述:
一行输出最后剩下的数字。

输入例子1:
500

输出例子1:
255
*/
#include<iostream>
#include<cstring>
int main() {
	int n;
	while(std::cin>>n)
	{
		int a[n+2];
		for(int i=0;i<=n;i++)
		{
			a[i]=1;
		}
		int result=0;
		int d=0;
		int ok=1;
		while(1)
		{
			if(!ok)
				break;
			int count=1;
			for(int i=0;i<=n;i++)
			{
				if(a[i]==1)
				{
					if(count%2==0)
						d=i;
					if(count%2==1)
					{
						a[i]=0;
						result++;
					}
					count++;
					if(result==n)
					{
						std::cout<<d<<std::endl;
						ok=0;
						break;
					}
				}
			}
		}
	}
}
