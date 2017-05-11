//如果一个自然数的所有小于自身的因子之和等于该数，则称为完数。设计算法，打印1-9999之间的所有完数。
#include<iostream>
#include<cstring>   
using namespace std;  
#define max(a,b) ((a)>(b)?(a):(b)) 
int addNum(int a)
{
	int add=0;
	for(int i=1;i<=a/2;i++)
	{
		if(a%i==0)
			add+=i;
	}
	return add;
}
int main()
{
	int a=1;
	for(;a<=9999;a++)
	{
		if(addNum(a)==a)
			cout<<a<<endl;
	}
}
