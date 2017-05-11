#include	<iostream>
#include <algorithm>
using namespace std;
int main()
{
	int a[15],b[15];
	for(int i=0;i<10;i++)
	{
		cin>>a[i];
	}
	sort(a,a+10);
	for(int i=0;i<10;i++)
	{
		if(i==0||a[i]!=a[i-1]){
			cout<<a[i]<<endl;
		}
	}
}
