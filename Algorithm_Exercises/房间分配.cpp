/*
n个房间，第i号的房间人需要重新分配
i号房间人都出来
然后按照i+1,i+2的顺序依次放人
n号房间的下一号是1号房间
直到所有人被重新分配
已知告诉了分配完后每个房间的人数以及最后一个人被分配的房间号
第一行两个整数n,x表示房间数量和最后一个房间号
第二行n个数，表示每个房间分配后的人数
*/
#include<iostream>
#include<vector>
#include<cstdio>
int main()
{
	int n,last;
	std::cin>>n>>last;
	std::vector<int> v(n);
	for(int i=0;i<n;i++)
	{
		scanf("%d",&v[i]);
	}
	int count=0;
	int index=last-1;
	while(1)
	{
		v[index]--;
		count++;
		if(v[index]<0)
		{
			v[index]+=count;
			break;
		}
		if(index-1<0)
			index=n-1;
		else
			index--;
	}
	for(int i=0;i<v.size();i++)
	{
		if(i<v.size()-1)
			printf("%d ",v[i]);
		else
			printf("%d\n",v[i]);
	}
}
