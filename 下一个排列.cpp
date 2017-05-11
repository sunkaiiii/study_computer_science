/*
下一个排列，求出一个数组的全部排列方式
*/
#define _CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES 1
#define _CRT_SECURE_NO_DEPRECATE
#define _CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES 1
#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;
int main()
{
	int n, p[10];
	cin >> n;
	for (int i = 0; i < n; i++)
		cin >> p[i];
	sort(p, p + n);
	do {
		for (int i = 0; i < n; i++)
			cout << p[i] << " ";
		cout << endl;
	} while (next_permutation(p, p + n));
}