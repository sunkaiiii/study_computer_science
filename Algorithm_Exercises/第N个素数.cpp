#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;
int a[100000000];
int main()
{
	int N = 100000000;
	int x = 1;
	for (int i = 2; i < N / 2; i++)
	{
		if (a[i] == 1)
			continue;
		for (int k = 2; k <= N / i; k++)
		{
			if (i*k < N)
				a[i*k] = 1;
		}
	}
	int m = 0;
	for (int i = 2; i < N; i++)
	{
		if (a[i] == 0)
		{
			m++;
			if (m == x)
				cout << i << " ";
		}
	}
}