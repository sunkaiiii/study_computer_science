#include <iostream>
#include <algorithm>
#include<ctime>
#include<vector>
int main()
{
	int a[30];
	srand((int)time(0));
	for(int i=0;i<30;i++)
	{
		a[i]=rand()%100;
	}
	std::sort(a,a+30);
	for(int i=0;i<30;i++)
	{
		std::cout<<a[i]<<",";
	}
	std::cout<<std::endl;
	std::cout<<"test binary search\n";
	if(std::binary_search(a,a+30,4))
		std::cout<<"4 is in the array\n";
	else
		std::cout<<"4 is not in the array\n";
	std::cout<<"test count\n";
	std::cout<<"count 13 is "<<std::count(a,a+30,13)<<std::endl;
	int b[30];
	for(int i=0;i<30;i++)
	{
		b[i]=rand()%30;
	}
	std::sort(b,b+30);
	std::vector<int> c(60);
	std::cout<<"test merge\nthis is b:\n";
	for(int i=0;i<30;i++)
	{
		std::cout<<b[i]<<",";
	}
	std::cout<<std::endl;
	std::merge(a,a+30,b,b+30,c.begin());
	std::cout<<"this is merge\n";
	for(auto i=c.begin();i!=c.end();i++)
	{
		std::cout<<*i<<",";
	}
	std::cout<<std::endl;
	std::cout<<"test make heap\n";
	for(int i=0;i<30;i++)
	{
		b[i]=rand()%30;
	}
	std::cout<<"this is array:\n";
	for(int i=0;i<30;i++)
	{
		std::cout<<b[i]<<",";
	}
	std::cout<<std::endl;
	std::make_heap(b,b+30);
	std::cout<<"init max heap:"<<b[0]<<"\nthis is all heap:\n";
	for(int i=0;i<30;i++)
	{
		std::cout<<b[i]<<",";
	}
	std::cout<<std::endl;
}
