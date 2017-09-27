/*[编程题] 工作安排
时间限制：1秒
空间限制：32768K
现在有n位工程师和6项工作(编号为0至5)，现在给出每个人能够胜任的工作序号表(用一个字符串表示，比如：045，表示某位工程师能够胜任0号，4号，5号工作)。现在需要进行工作安排，每位工程师只能被安排到自己能够胜任的工作当中去，两位工程师不能安排到同一项工作当中去。如果两种工作安排中有一个人被安排在的工作序号不一样就被视为不同的工作安排，现在需要计算出有多少种不同工作安排计划。 
输入描述:
输入数据有n+1行：
第一行为工程师人数n(1 ≤ n ≤ 6)
接下来的n行，每行一个字符串表示第i(1 ≤ i ≤ n)个人能够胜任的工作(字符串不一定等长的)


输出描述:
输出一个整数，表示有多少种不同的工作安排方案

输入例子1:
6
012345
012345
012345
012345
012345
012345

输出例子1:
720
*/
#include<iostream>
#include<algorithm>
#include<string.h>
#include<vector>
#include<math.h>
using namespace std;
long long count2=0;
void f(char a[10][1000],int b[10][10000],int d[10000],int i,int n)
{
	if(i==n)
	{
		count2=count2+1;
		return;
	}
	else
	{
		for(int i2=0;i2<strlen(a[i]);i2++)
		{
			if(d[b[i][i2]]==0)
			{
				d[b[i][i2]]=1;
				f(a,b,d,i+1,n);
				d[b[i][i2]]=0;
			}

		}
	}
}
int main()
{
	int n;
	cin>>n;
	char a[10][1000];
	int d[10000];
	memset(d,0,sizeof(d));
	int max=0;
	for(int i=0;i<n;i++)
	{
		cin>>a[i];
		if(strlen(a[i])>max)
		{
			max=strlen(a[i]);
		}
	}	
	int b[10][10000];
	for(int i=0;i<n;i++)
	{
		for(int i2=0;i2<strlen(a[i]);i2++)
		{
			b[i][i2]=a[i][i2]-'0';
		}
	}
	f(a,b,d,0,n);
	cout<<count2<<endl;
} 
