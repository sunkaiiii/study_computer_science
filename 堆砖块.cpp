/*[编程题] 堆砖块
时间限制：1秒
空间限制：32768K
小易有n块砖块，每一块砖块有一个高度。小易希望利用这些砖块堆砌两座相同高度的塔。为了让问题简单，砖块堆砌就是简单的高度相加，某一块砖只能使用在一座塔中一次。小易现在让能够堆砌出来的两座塔的高度尽量高，小易能否完成呢。 
输入描述:
输入包括两行：
第一行为整数n(1 ≤ n ≤ 50)，即一共有n块砖块
第二行为n个整数，表示每一块砖块的高度height[i] (1 ≤ height[i] ≤ 500000)


输出描述:
如果小易能堆砌出两座高度相同的塔，输出最高能拼凑的高度，如果不能则输出-1.
保证答案不大于500000。

输入例子1:
3
2 3 5

输出例子1:
5
*/
#include<iostream>
#include<algorithm>
#define MAXVALUE 500000
int result=0;
int a[500];
void f(int h1,int h2,int n,int shengyu)
{
	if(h1==h2)
	{
		result=std::max(result,h1);
	}
	if(n<0)
	{
		return;
	}
	if(std::max(h1,h2)>MAXVALUE)
	{
		return;
	}
	if(std::min(h1,h2)+shengyu<std::max(h1,h2))
	{
		return;
	}
	if(h1+h2+shengyu<=result*2)
	{
		return;
	}
	f(h1+a[n],h2,n-1,shengyu-a[n]);
	f(h1,h2+a[n],n-1,shengyu-a[n]);
	f(h1,h2,n-1,shengyu-a[n]);

}
int main()
{
	
	int n;
	std::cin >> n;
	int maxHeight = 0;
	for (int i = 0; i < n; i++)
	{
		std::cin >> a[i];
		maxHeight += a[i];
	}
	std::sort(a,a+n);
	f(0,0,n-1,maxHeight);
	if(result==0)
		std::cout<<-1<<std::endl;
	else
		std::cout<<result<<std::endl;
}
