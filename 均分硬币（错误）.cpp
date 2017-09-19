#include<iostream>
#include<cmath>
int a[100001];
int main()
{
	int n;
	std::cin>>n;
	long long add=0;
	for(int i=0;i<n;i++)
	{
		std::cin>>a[i];
		add+=a[i];
	}
	if(add%n!=0)
	{
		std::cout<<-1<<std::endl;
	}
	long long avg=add/n;
	long long result=0;
	for(int i=0;i<n;i++)
	{
		if(a[i]<avg)
		{
			result+=(avg-a[i]);
		}
	}
	std::cout<<result<<std::endl;
}
