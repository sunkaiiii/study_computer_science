/*
二维数组打印
时间限制：3秒
空间限制：32768K
有一个二维数组(n*n),写程序实现从右上角到左下角沿主对角线方向打印。
给定一个二位数组arr及题目中的参数n，请返回结果数组。
测试样例：
[[1,2,3,4],[5,6,7,8],[9,10,11,12],[13,14,15,16]],4
返回：[4,3,8,2,7,12,1,6,11,16,5,10,15,9,14,13]
*/
#include<iostream>
#include<cstring>
#include<vector>
#include<algorithm>
class Printer{
public:
	std::vector<int> arrayPrint(std::vector<std::vector<int>> arr,int n)
	{
		int a[n];
		std::vector<int> v;
		a[0]=0;
		for(int i=1;i<n;i++)
		{
			a[i]=a[i-1]-1;
		}
		for(int i=0;i<n;i++)
		{
			std::reverse(arr[i].begin(),arr[i].end());
		}
		while(a[n-1]<n)
		{
			for(int j=0;j<n;j++)
			{
				if(a[j]<n&&a[j]>=0)
				{
					v.push_back(arr[j][a[j]]);
					//std::cout<<arr[j][a[j]]<<" ";
				}
				a[j]++;
			}
		}
		return v;
	}
};
int main()
{
	int count=1;
	std::vector<int> w1;
	std::vector<int> w2;
	std::vector<int> w3;
	std::vector<int> w4;
	std::vector<std::vector<int>> x;
	x.push_back(w1);
	x.push_back(w2);
	x.push_back(w3);
	x.push_back(w4);
	for(int i=0;i<4;i++)
	{
		for(int j=0;j<4;j++)
		{
			x[i].push_back(count);
			count++;
		}
	}
	Printer c;
	c.arrayPrint(x,4);
}
