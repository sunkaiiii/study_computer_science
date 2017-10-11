/*
密码等级
  时间限制：C/C++语言 3000MS；其他语言 5000MS
内存限制：C/C++语言 65536KB；其他语言 589824KB
题目描述：
用户的密码分为4个等级，具体定义如下：
等级0：密码小于8位/密码与用户名一样或相反/只包含4类字符中的任意一类
等级1：大于等于8位包含两类字符，且组合为(数字+小写字母)或(数字+大写字母)
等级2：大于等于8位包含两类字符，且组合不能为(数字+小写字母)和(数字+大写字母)
等级3：大于等于8位包含三类以上字符
其中4类字符为：数字，小写字母，大写字母，特殊字符(除了数字，小写字母，大写字母外的字符)
输入
第一行输入用户名 密码，用户和密码用空格分开(密码中不会包含空格)
输出
输出具体密码强度
样例输入
admin 112233
样例输出
0
*/
#include<iostream>
#include<string>
#include<algorithm>
#include<vector>
using std::endl;
int main()
{
	std::string name(""),password;
	// std::cin>>name>>password;
	std::string s;
	std::vector<std::string> v;
	while(std::cin>>s)
	{
		v.push_back(s);
	}
	password=v[v.size()-1];

	for(int i=0;i<v.size()-1;i++)
	{
		if(i!=v.size()-2)
		{
			name=name+v[i]+" ";
		}
		else
		{
			name+=v[i];
		}
	}
	// std::cout<<name<<" "<<password<<endl;
	if(name.size()<8||password.size()<8)
	{
		std::cout<<0<<endl;
		return 0;
	}
	if(name==password)
	{
		std::cout<<0<<endl;
		return 0;
	}
	std::string reverse_password(password);
	std::reverse(reverse_password.begin(),reverse_password.end());
	if(name==reverse_password)
	{
		std::cout<<0<<endl;
		return 0;
	}
	bool number=false,xiaoxie=false,daxie=false,other=false;
	int result=0;
	for(auto i=password.begin();i!=password.end();i++)
	{
		if(*i>='0'&&*i<='9')
			number=true;
		else if(*i>='A'&&*i<='Z')
			daxie=true;
		else if(*i>='a'&&*i<='z')
			xiaoxie=true;
		else
			other=true;
	}
	if(number)
		result++;
	if(daxie)
		result++;
	if(xiaoxie)
		result++;
	if(other)
		result++;
	if(result>=3)
	{
		std::cout<<3<<endl;
		return 0;
	}
	if(result<=1)
	{
		std::cout<<0<<endl;
		return 0;
	}
	if((number&&xiaoxie&&!daxie&&!other)||(number&&daxie&&!xiaoxie&&!other))
	{
		std::cout<<1<<endl;
		return 0;
	}
	if((!number&&!xiaoxie)||(!number&&!daxie))
	{
		std::cout<<2<<endl;
		return 0;
	}
	return 0;
}
