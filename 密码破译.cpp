#include<iostream>
#include<cstring>
void f(char s[1000000],int length,int index,std::string result,int num,int sub,int add)
{
	if(index>=length)
	{
		int add2=0;
		for(auto i=result.begin();i!=result.end();i++)
		{
			int i2=*i-96;
			if(i2<10)
				add2=add2+i2;
			else
			{
				while(i2>0)
				{
					add2=add2+i2%10;
					i2/=10;
				}
			}
		}
		if(add2==add)
			std::cout<<result<<" ";
		return;
	}
	else
	{
		if(num*10+(s[index]-48)<=26&&num!=0)
		{
			num=num*10+(s[index]-48);
			std::string s3=result;
			s3.push_back(num+96);
			sub--;
			f(s,length,index+1,s3,num,sub,add);
		}
		num=s[index]-48;
		std::string s4=result;
		s4.push_back(num+96);
		sub--;
		f(s,length,index+1,s4,0,sub,add);
		sub++;
		f(s,length,index+1,result,num,sub,add);
	}
}
int main()
{
	char s[1000000];
	std::string result;
	while(std::cin>>s)
	{
		char s2[1000000];
		strcpy(s2,s);
		int add=0;
		for(int i=0;i<strlen(s2);i++)
		{
			add=add+s2[i]-'0';
		}
		f(s,strlen(s),0,result,0,strlen(s),add);
		std::cout<<std::endl;
	}
}
