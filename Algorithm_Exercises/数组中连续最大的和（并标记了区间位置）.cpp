#include<iostream>
#include<cstring>
int findMax(int a[],int n)
{
	if(n<=0)
	{
		return 0;
	}
	if(n==1)
		return a[0];
	int temp=0;
	int max=a[0];
	int maxindex=0;
	int result=0;
	int start=0;
	int tempstart;
	int end;
	for(int i=0;i<n;i++)
	{
		temp+=a[i];
		if(temp<0)
		{
			temp=0;
			tempstart=i+1;
		}
		else if(result<temp)
		{
			start=tempstart;
			result=temp;
			end=i;
		}
		if(max<a[i]) //防止全负数的情况
		{
			max=a[i];
			maxindex=i;
		}
	}
	if(result==0)
	{
		std::cout<<"xiabiao:"<<maxindex<<std::endl;
		return max;
	}
	std::cout<<"xiabiao:"<<start<<" "<<end<<std::endl;
	return result;
}
int main()
{
	int n;
	while(std::cin>>n)
	{
		int a[n];
		for(int i=0;i<n;i++)
		{
			std::cin>>a[i];
		}
		int result=findMax(a,n);
		std::cout<<result<<std::endl;
	}
}
