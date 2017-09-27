/*
[编程题] 涂棋盘
时间限制：1秒
空间限制：32768K
小易有一块n*n的棋盘，棋盘的每一个格子都为黑色或者白色，小易现在要用他喜欢的红色去涂画棋盘。小易会找出棋盘中某一列中拥有相同颜色的最大的区域去涂画，帮助小易算算他会涂画多少个棋格。 
输入描述:
输入数据包括n+1行：

第一行为一个整数n(1 ≤ n ≤ 50),即棋盘的大小

接下来的n行每行一个字符串表示第i行棋盘的颜色，'W'表示白色，'B'表示黑色


输出描述:
输出小易会涂画的区域大小

输入例子1:
3
BWW
BBB
BWB

输出例子1:
3
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
	int n;
	std::cin>>n;
	char a[n+2][n+2];
	for(int i=0;i<n;i++)
	{
		for(int i2=0;i2<n;i2++)
		{
			std::cin>>a[i][i2];
		}
	}
	int max=0;
	int b,w;
	int count=0;
	for(int i2=0;i2<n;i2++)
	{
		count=0;
		int sym;
		int max2=0;
		for(int i=0;i<n;i++)
		{	
			if(i==0)
			{
				count++;
				sym=a[i][i2];
			}
			else
			{
				if(a[i][i2]==sym)
					count++;
				else
				{
					if(count>max2)
					{
						max2=count;					
					}
					sym=a[i][i2];
					count=1;
				}
			}
		}
		if(count>max2)
		{
			max2=count;		
		}
		max=std::max(max,max2);
	}
	std::cout<<max<<std::endl;
} 
