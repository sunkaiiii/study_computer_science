/*
小易参与了一个记单词的小游戏。游戏开始系统提供了m个不同的单词，小易记忆一段时间之后需要在纸上写出他记住的单词。小易一共写出了n个他能记住的单词，如果小易写出的单词是在系统提供的，将获得这个单词长度的平方的分数。注意小易写出的单词可能重复，但是对于每个正确的单词只能计分一次。 
输入描述:
输入数据包括三行：

第一行为两个整数n(1 ≤ n ≤ 50)和m(1 ≤ m ≤ 50)。以空格分隔

第二行为n个字符串，表示小易能记住的单词，以空格分隔，每个单词的长度小于等于50。

第三行为m个字符串，系统提供的单词，以空格分隔，每个单词的长度小于等于50。


输出描述:
输出一个整数表示小易能获得的分数

输入例子1:
3 4
apple orange strawberry
strawberry orange grapefruit watermelon

输出例子1:
136
*/
#include<iostream>
#include<algorithm>
#include<string.h>
#include<cmath>
#include<set>
int result=0;
int main()
{
	int n,m;
	std::cin>>n>>m;
	char a[50][500];
	char b[50][500];
	std::set<char*> aset;
	for(int i=0;i<n;i++)
	{
		std::cin>>a[i];
	}
	for(int i=0;i<m;i++)
	{
		std::cin>>b[i];
	}
	for(int i=0;i<n;i++)
	{
		char *test=a[i];
		//std::cout<<test<<std::endl;
		for(int i2=0;i2<m;i2++)
		{
			char *testb=b[i2];
			if(strlen(test)!=strlen(testb))
			{
				continue;
			}
			std::set<char*>::iterator it;
			int ok=1;
			for(it=aset.begin();it!=aset.end();it++)
			{
				if(strlen(*it)==strlen(test))
				{
					if(strcmp(*it,test)==0)
					{
						ok=0;
						break;
					}
				}
			} 
			if(ok==0)
			{
				break;
			}
			if(strcmp(test,testb)==0)
			{
				aset.insert(a[i]);
				result=result+strlen(test)*strlen(test);
				break;
			}
		}
	}
	std::cout<<result<<std::endl;
}
