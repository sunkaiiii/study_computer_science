#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;
void f(char data[],int a)
{
	if(a==strlen(data)-1)
		cout << data << endl;
	for (int i = a; i < strlen(data); i++)
	{
		char b;
		b = data[a];
		data[a] = data[i];
		data[i] = b;
		f(data, a + 1);
		b = data[a];
		data[a] = data[i];
		data[i] = b;
	 }
}
int main()
{
	char data[20] = "ABCDE";
	f(data,0);
}