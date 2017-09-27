/*
K 的倍数
时间限制：C/C++语言 2000MS；其他语言 4000MS
内存限制：C/C++语言 65536KB；其他语言 589824KB
题目描述：
序列中任意个连续的元素组成的子序列称为该序列的子串。
现在给你一个序列P和一个整数K，询问元素和是K的倍数的子串的最大长度。
比如序列【1,2,3,4,5】，给定的整数K为 5，其中满足条件的子串为{5}、{2,3}、{1,2,3,4}、{1,2,3,4,5}，
那么答案就为 5，因为最长的子串为{1,2,3,4,5}；如果满足条件的子串不存在，就输出 0。
输入
第一含一个整数N, 1 ≤ 𝑁 ≤ 105 。
第二行包含 N 个整数𝑝𝑖 ，𝑝𝑖 表示序列P第i个元素的值。0 ≤ 𝑝𝑖 ≤ 105 。
第三行包含一个整数 K， 1 ≤ 𝐾 ≤ 105  。
输出
输出一个整数ANS，表示答案。

样例输入
Input Sample 1
5
1 2 3 4 5
5
Input Sample 2
6
3 1 2 7 7 7
4
样例输出
Output Sample 1
5
Output Sample 2
5
*/
#include<iostream>
#include<cstring>
#include<algorithm>
int main() {
	int n;
	std::cin>>n;
	int a[n];
	long long add=0;
	for(int i=0;i<n;i++)
	{
		std::cin>>a[i];
		add+=a[i];
	}
	int k;
	std::cin>>k;
	if(add%k==0)
	{
		std::cout<<n<<std::endl;
		return 0;
	}
	int result=0;
	int ok=1;
	for(int i=0;i<n;i++)
	{
		if(!ok)
			break;
		long long count=0;
		for(int j=i;j<n;j++)
		{
			count+=a[j];
			if(result>=n-i)
			{
				ok=0;
				break;
			}
			if(result>=j-i+1)
				continue;
			if(count%k==0)
			{
					result=j-i+1;
			}
		}
	}
	std::cout<<result<<std::endl;
}
