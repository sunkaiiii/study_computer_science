/*
n门考试，平均分至少达到avg
每门课的满分为r
小明第i门课只能考ai分
可以花一些祝福值增加，但是不能超过满分
小明可以花费bi祝福提高成绩1分
最终使平均分大于avg分
问需要多少祝福值
5 5 4
5 2
4 7
3 1
3 2
2 5
输出 4
*/
#include<iostream>
#include<map>
using std::endl;
int main()
{
	long long n,r,avg;
	std::cin>>n>>r>>avg;
	std::multimap<long long,long long> chengji;
	long long ai,bi;
	double pre_avg=0;
	for(long long i=0;i<n;i++)
	{
		std::cin>>ai>>bi;
		chengji.insert(std::pair<long long,long long>(bi,ai));
		pre_avg+=ai;
	}
	long long mubiao=avg*n;
	// std::cout<<pre_avg<<" "<<mubiao<<endl;
	long long result=0;
	for(auto i=chengji.begin();i!=chengji.end()&&pre_avg<=mubiao;i++)
	{
		long long chengji2=i->second;
		long long sub=r-chengji2;
		if(pre_avg+sub<mubiao)
		{
			pre_avg+=sub;
			result=result+(sub*i->first);
			//std::cout<<pre_avg<<"\n";
		}
		else
			while(chengji2<r&&pre_avg<mubiao)
			{
				pre_avg++;
				result+=i->first;
			}
	}
	std::cout<<result<<endl;
}
