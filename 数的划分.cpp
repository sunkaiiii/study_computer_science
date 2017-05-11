#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;
void f(int n, int a[], int k)
{
	if (n <= 0)
	{
		for (int i = 0; i < k; i++)
			cout << a[i] << " ";
		cout << endl;
		return;
	}
	for (int i = n; i >= 1; i--)
	{
		if (k > 0 && i > a[k - 1])
			continue;
		a[k] = i;
		f(n - i, a, k + 1);
	}
}
int main()
{
	int a;
	int b[100000];
	cin >> a;
	f(a, b, 0);
}