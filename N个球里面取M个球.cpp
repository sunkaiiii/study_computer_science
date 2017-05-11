#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;
int f(int n, int m)
{
	if (n < m)
		return 0;
	else if (n == m)
		return 1;
	else if (m <= 0)
		return 1;
	else 
		return f(n - 1, m - 1) + f(n - 1, m);
}
int main()
{
	int m, n;
	cin >> m >> n;
	int k=f(m, n);
	cout << k << endl;
}