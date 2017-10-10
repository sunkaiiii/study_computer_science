/*
小明喜欢在火车旅行的时候用手机听音乐
他有N首歌在手机里
他可以听P首歌
他想产生一个播放列表，其中有P首歌曲
规则是
1、每首歌至少被博一次
2、在两首一样的歌中间，至少有M首其他的歌

给出NMP输出结果对1000000007求余

输入 1 0 3
输出 1
*/
#include<iostream>
#include<vector>
#include<algorithm>
using std::endl;
#define NONUM -99999
#define mod 1000000007
long long a[102][102];
int n,m,p;
long long f(int i,int j)
{
	if(a[i][j]!=NONUM)
		return a[i][j];
	if(i==p)
	{
		if(j==n)
		{
			a[i][j]=1;
			return 1;
		}
		else
		{
			a[i][j]=0;
			return 0;
		}
	}
	a[i][j]=0;
	if(j>m)
		a[i][j]=f(i+1,j)*(j-m);
	if(j<n)
		a[i][j]+=f(i+1,j+1)*(n-j);
	if(a[i][j]>=mod)
		a[i][j]%=mod;
	return a[i][j];
}
int main()
{
	std::cin>>n>>m>>p;
	for(int i=0;i<=p;i++)
		for(int j=0;j<=n;j++)
		{
			a[i][j]=NONUM;
		}

	std::cout<<f(0,0)<<endl;
}
