/*
字符串分隔
  时间限制：C/C++语言 3000MS；其他语言 5000MS
内存限制：C/C++语言 65536KB；其他语言 589824KB
题目描述：
给定一个字符串及分隔符，字符串和分隔符之间以空格分开(分隔符中不会包含空格)要求根据该分隔符进行拆分，每个小的字符串输出为一行。
输入
第一行输入原始字符串 分隔符，原始字符串和分隔符空格分开(分隔符中不会包含空格)
输出
输出分隔好后的每个字符串，每个字符串以换行符分开
样例输入
abc,def,ghi,jkl ,
样例输出
abc
def
ghi
jkl
*/
#include<iostream>
#include<string>
#include<vector>
using std::endl;
std::string s2;
std::string s;
int main()
{
	std::vector<std::string> v;
	while(std::cin>>s2)
	{
		v.push_back(s2);
	}
	char split;
	// std::cin>>s>>split;
	split=*v[v.size()-1].begin();
	for(int i=0;i<v.size()-1;i++)
	{
		if(i!=v.size()-2)
		{
			s=s+v[i]+" ";
		}
		else
		{
			s+=v[i];
		}
	}
	int count=0;
	for(auto i=s.begin();i!=s.end();i++)
	{
		if(*i!=split)
		{
			std::cout<<*i;
			count++;
		}
		else if(count>0)
		{
			std::cout<<endl;
			count=0;
		}
	}
	if(count)
		std::cout<<endl;
}
