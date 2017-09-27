#include<iostream>
#include<cstring> 
using namespace std;
int main()
{
	int a[50][50];
	memset(a, 0, sizeof(a));
	int b;
	cin >> b;
	int d, e;
	a[0][0] = 1;
	a[1][0] = 1;
	a[1][1] = 1;
	for (d = 0; d < b; d++)
	{
		for (e = 0; e <= d; e++)
		{
			if (e == 0)
				a[d][e] = 1;
			else
				a[d][e] = a[d - 1][e] + a[d - 1][e - 1];
		}
	}
	for (d = 0; d < b; d++)
	{
		for (e = 0; e <= d; e++)
		{
			cout << a[d][e] << " ";
		}
		cout << endl;
	}
}
