/*
（图３.１－１）示出了一个数字三角形。 请编一个程序计算从顶至底的某处的一条路
　　径，使该路径所经过的数字的总和最大。
　　●每一步可沿左斜线向下或右斜线向下走；
　　●1＜三角形行数≤100；
　　●三角形中的数字为整数0，1，…99；


　　.
　　（图３.１－１）
输入格式
　　文件中首先读到的是三角形的行数。

　　接下来描述整个三角形
输出格式
　　最大总和（整数）
样例输入
5
7
3 8
8 1 0
2 7 4 4
4 5 2 6 5
样例输出
30
*/ 
#include	<iostream>
#include	<string.h>
using namespace std;
int a[200][200];
long long maxs[200][200];
int ceng;
int main()
{
	cin>>ceng;
	for(int i=1;i<=ceng;i++)
	{
		for(int i2=0;i2<i;i2++)
		{
			cin>>a[i][i2];
		}
	}
	for(int i=ceng;i>=1;i--)
	{
		for(int i2=0;i2<i;i2++)
		{
			if(i==ceng)
			{
				maxs[i][i2]=a[i][i2];
			}
			else
			{
				maxs[i][i2]=((maxs[i+1][i2]>maxs[i+1][i2+1])?maxs[i+1][i2]:maxs[i+1][i2+1])+a[i][i2];
			}
		}
	}
	cout<<maxs[1][0]<<endl;
}
