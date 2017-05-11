#include<iostream>
#include<cstring> 
using namespace std;
int a[1000001];
int main()
{
	int b,c;
	memset(a,0,sizeof(a));
	cin>>b;
	a[0]=1;
	a[1]=1;
	if(b<=2)
	{
		cout<<"1\n";
	}
	else
	{
		for(c=2;c<b;c++)
		{
			a[c]=(a[c-1]+a[c-2])%10007;
		}
	cout<<a[b-1]<<endl;
	}
}
