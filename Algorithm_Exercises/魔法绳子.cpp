/*
N个玩具，M个绳子
玩具之间最多连一条绳子
取这个玩具需要消耗能量
消耗量为与这个直接相连的玩具的能量值
消耗最少多少能量
*/
#include<iostream>
#include<vector>
#include<map>
#include<algorithm>
using std::endl;
int main()
{
	int n,m;
	std::cin>>n>>m;
	std::vector<int> toy(n);
	for(int i=0;i<n;i++)
	{
		std::cin>>toy[i];
	}
	std::multimap<int,int> shengzi;
	std::vector<int> shengzilianjie(n+1,0);
	int from,to;
	for(int i=0;i<m;i++)
	{
		std::cin>>from>>to;
		shengzi.insert(std::pair<int,int>(from,to));
		shengzilianjie[from]++;
		shengzilianjie[to]++;
	}
	int count=0;
	long long result=0;
	while(count<m)
	{
		std::vector<int> v;
		for(int i=1;i<shengzilianjie.size();i++)
		{
			// std::cout<<i<<" "<<shengzilianjie[i]<<"\n";
			if(shengzilianjie[i]==1)
				v.push_back(i);
		}
		int min=-1;
		int indexfrom=-1;
		int indexto=-1;
		for(int i:v)
		{
			for(auto i2=shengzi.begin();i2!=shengzi.end();i2++)
			{
				if(i2->first==i||i2->second==i)
				{
					if(i2->first==i)
					{
						if(min==-1)
						{
							min=toy[i2->second-1];
							indexfrom=i;
							indexto=i2->second;
						}
						else
						{
							if(min>toy[i2->second-1])
							{
								min=toy[i2->second-1];
								indexfrom=i;
								indexto=i2->second;
							}
						}
					}
					else
					{
						if(min==-1)
						{
							min=toy[i2->first-1];
							indexfrom=i;
							indexto=i2->first;
						}
						else
						{
							if(min>toy[i2->first-1])
							{
								min=toy[i2->first-1];
								indexfrom=i;
								indexto=i2->first;
							}
						}
					}
				}
			}
		}
		count++;
		std::cout<<indexto<<" "<<indexfrom<<min<<endl;
		if(indexto!=-1&&indexfrom!=-1)
		{
			shengzilianjie[indexto]--;
			shengzilianjie[indexfrom]--;
			result+=min;
		}
	}
	std::cout<<result<<endl;
}
