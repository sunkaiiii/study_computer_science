#include	<iostream>
#include	<string.h>
using namespace std;
int a[200][200];
int maxs[200];
int maxv[200];
int ceng;
int k;
long long maxValue;
// int calMax(int value,int nceng)
// {
// 	for(;nceng<=ceng;nceng++)
// 	{
// 		value+=maxs[nceng];
// 	}
// 	return value;
// }
void cal(int nceng,int k,long long value)
{
	if(nceng>ceng)
	{
		if(value>maxValue)
			maxValue=value;
		return;
	}
	else if(value+maxv[nceng]>maxValue)
	{
		//cout<<value<<",";
		value+=a[nceng][k];
		cal(nceng+1,k,value);
		value-=a[nceng][k];
		value+=a[nceng][k+1];
		cal(nceng+1,k+1,value);
		value-=a[nceng][k+1];
	}
}
int main()
{
	cin>>ceng;
	for(int i=1;i<=ceng;i++)
	{
		int cm=0;
		for(int i2=0;i2<i;i2++)
		{
			cin>>a[i][i2];
			if(cm<a[i][i2])
				cm=a[i][i2];
		}
		maxs[i]=cm;
	}
	for(int i=1;i<=ceng;i++)
	{
		maxv[i]=0;
		for(int i2=i;i2<=ceng;i2++)
		{
			maxv[i]+=maxs[i2];
		}
	}
	maxValue=0;
	cal(2,0,a[1][0]);
	cout<<maxValue;
}
