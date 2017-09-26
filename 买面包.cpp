#include<iostream>
int main()
{
	int n;
	std::cin>>n;
	int a[n+2];
	for(int i=0;i<n;i++)
	{
		std::cin>>a[i];
	}
	int m;
	std::cin>>m;
	int b[n+2];
	for(int i=0;i<n+2;i++)
	{
		b[i]=0;
	}
	for(int i=0;i<m;i++)
	{
		int x,y;
		std::cin>>x>>y;
		b[x]+=y;
	}
	int result=0;
	for(int i=1;i<=n;i++)
	{
		result=result+b[i]*a[i-1];
		//std::cout<<result<<",";
	}
	//std::cout<<std::endl;
	std::cout<<result<<std::endl;
}
