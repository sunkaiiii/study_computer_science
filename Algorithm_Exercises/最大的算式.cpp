#include	<iostream>
#include	<string.h>
using namespace std;
int a[20];
int n;
int k;
long long maxValue;
void cal(int nc,int nn,int nk,long long value)
{
	if(nc==n)
	{
		if(value>maxValue)
			maxValue=value;
		return;
		
	}
	else
	{
		//cout<<value<<",";
		if(nn<(n-k-1))
		{
			int aa=value;
			value+=a[nc];
			cal(nc+1,nn+1,nk,value);
			value=aa;
		}
		if(nk<k)
		{
			int aa=value;
			value*=a[nc];
			cal(nc+1,nn,nk+1,value);
			value=aa;
		}
	}
}
int main()
{

	cin>>n>>k;
	memset(a,0,sizeof(a));
	for(int i=0;i<n;i++)
	{
		cin>>a[i];
	}
	maxValue=0;
	cal(1,0,0,a[0]);
	cout<<maxValue<<endl;
}
