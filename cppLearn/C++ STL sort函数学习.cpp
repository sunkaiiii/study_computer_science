#include <iostream>
#include <algorithm>
#include <vector>
class testsort{
public:
	int first,second;
	testsort(int f,int s)
	:first(f),second(s)
	{	}

	bool operator < (const testsort &scond)const
	{
		return first<scond.first;
	}
};
bool less_second(const testsort &t1,const testsort &t2)
{
	return t1.second<t2.second;
}
int main()
{
	std::vector<testsort> v;
	for(int i=5;i>=0;i--)
	{
		testsort s(i,10-i);
		v.push_back(s);
	}
	for(int i=5;i<10;i++)
	{
		testsort s(i,10-i);
		v.push_back(s);
	}
	std::cout<<"normal vector";
	for(auto i=v.begin();i!=v.end();i++)
	{
		std::cout<<testsort(*i).first<<","<<testsort(*i).second<<std::endl;
	}
	std::cout<<"-------------------------------------------\n";
	sort(v.begin(),v.end());
	std::cout<<"sort by function1\n";
	for(auto i=v.begin();i!=v.end();i++)
	{
		std::cout<<testsort(*i).first<<","<<testsort(*i).second<<std::endl;
	}
	std::cout<<"-------------------------------------------\n";
	sort(v.begin(),v.end(),less_second);
	std::cout<<"sort by function2\n";
	for(auto i=v.begin();i!=v.end();i++)
	{
		std::cout<<testsort(*i).first<<","<<testsort(*i).second<<std::endl;
	}
	std::cout<<"-------------------------------------------\n";
	std::cout<<"partial sort test\n"; //其内部实现的方法是堆排序
	std::partial_sort(v.begin(),v.begin()+4,v.end());
	for(auto i=v.begin();i!=v.end();i++)
	{
		std::cout<<testsort(*i).first<<","<<testsort(*i).second<<std::endl;
	}
	std::cout<<"-------------------------------------------\n";
	std::cout<<"nth_elment test\n";
	std::nth_element(v.begin(),v.begin()+5,v.end());//使第n大的数处在第n位置
	for(auto i=v.begin();i!=v.end();i++)
	{
		std::cout<<testsort(*i).first<<","<<testsort(*i).second<<std::endl;
	}
	std::cout<<"-------------------------------------------\n";
	std::cout<<"partition test\n";
	testsort s(5,5);
	std::partition(v.begin(),v.end(),s);
	for(auto i=v.begin();i!=v.end();i++)
	{
		std::cout<<testsort(*i).first<<","<<testsort(*i).second<<std::endl;
	}
	std::cout<<std::endl;
	return 0;
}
