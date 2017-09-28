/*
搜狗 2018校招 搜狗输入法—C/C++开发工程师—Windows平台在线考试
编程题 | 50.0分1/1
钝角三角形个数
时间限制：C/C++语言 3000MS；其他语言 5000MS
内存限制：C/C++语言 30720KB；其他语言 555008KB
题目描述：
输入圆周上的n个点（n>=1），以角度a表示其位置(0<=a<360)，输入按a从小到大排序。求输入的点可以构成的钝角三角形个数。
输入
第一行为点个数n，后跟n行，每行一个双精度浮点数，表示点的角度（小数点后保留8位），例如输入样例中为4个点的输入：
输出
输出可以构成的钝角三角形个数和'\n'换行符。

样例输入
4
0.00000000
56.00000000
179.00000000
180.00000000
样例输出
2
*/
#include<cstdio>
#include<iostream>
using std::endl;
double a[300002];
int main()
{
	int n;
	std::cin>>n;
	for(int i=0;i<n;i++)
	{
		scanf("%lf",&a[i]);
	}
	int result=0;
	for(int i=0;i<n;i++)
	{
		for(int j=i+1;j<n;j++)
		{
			for(int k=j+1;k<n;k++)
			{
				int add=0;
				add=add+a[k]-a[j];
				add=add+a[j]-a[i];
				if(add<180)
					result++;
				else
					break;
			}
		}
	}
	std::cout<<result<<endl;
}
