#include<iostream>
#include<algorithm>
#define MAXVALUE 500000
int result=0;
int a[500];
void f(int h1,int h2,int n,int shengyu)
{
	if(h1==h2)
	{
		result=std::max(result,h1);
	}
	if(n<0)
	{
		return;
	}
	if(std::max(h1,h2)>MAXVALUE)
	{
		return;
	}
	if(std::min(h1,h2)+shengyu<std::max(h1,h2))
	{
		return;
	}
	if(h1+h2+shengyu<=result*2)
	{
		return;
	}
	f(h1+a[n],h2,n-1,shengyu-a[n]);
	f(h1,h2+a[n],n-1,shengyu-a[n]);
	f(h1,h2,n-1,shengyu-a[n]);

}
int main()
{
	
	int n;
	std::cin >> n;
	int maxHeight = 0;
	for (int i = 0; i < n; i++)
	{
		std::cin >> a[i];
		maxHeight += a[i];
	}
	std::sort(a,a+n);
	f(0,0,n-1,maxHeight);
	if(result==0)
		std::cout<<-1<<std::endl;
	else
		std::cout<<result<<std::endl;
}
