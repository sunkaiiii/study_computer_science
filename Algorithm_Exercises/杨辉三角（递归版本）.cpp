#include<iostream>
#include<cstring> 
using namespace std;
int f(int a, int b)
{
	if (a == 1)
		return 1;
	if (a == b)
		return 1;
	return f(a, b-1) + f(a - 1, b - 1);
}
int main()
{
	int a;
	cin >> a;
	int b, c,d;
	for (d= 1; d <= a; d++)
	{
		for (b = 1; b <= d; b++)
		{
			cout << f(b,d)<<" ";
		}
		cout << endl;
	}
}
