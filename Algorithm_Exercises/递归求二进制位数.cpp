//给定一个十进制整数，返回其对应的二进制数的位数。例如，输入十进制数9，其对应的二进制数是1001，因此位数是4。 
#include	<iostream>
using namespace std;
int main()
{
	int a;
	cin>>a;
	int count=0;
	while(a>0)
	{
		a/=2;
		count++;
	}
	cout<<count<<endl;
}
