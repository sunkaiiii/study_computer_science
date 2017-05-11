//输入正整数n，把证书1,2,3~n组成一个环，是的相邻两个整数之和均为素数，输出时从1开始逆时针排列，应恰好输出一次
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;
int isp[1000];
int A[1000];
int n;
int vis[100];
int is_prime(int i)
{
	int i2 = 2;
	for (; i2 < i; i2++)
	{
		if (i%i2 == 0)
			return 0;
	}
	return 1;
}
void dfs(int cur)
{
	if (cur == n&&isp[A[0] + A[n - 1]])
	{
		for (int i = 0; i < n; i++)
			cout << A[i] << " ";
		cout << endl;
	}
	else
		for (int i = 2; i <= n; i++)
		{
			if (!vis[i] && isp[i + A[cur - 1]])
			{
				A[cur] = i;
				vis[i] = 1;
				dfs(cur + 1);
				vis[i] = 0;
			}
		}
}
int main()
{
	memset(isp, 0, sizeof(isp));
	cin >> n;
	for (int i = 2; i <= n * 2; i++)
	{
		isp[i] = is_prime(i);
	}
	memset(vis, 0, sizeof(vis));
	A[0] = 1;
	//for (int i = 0; i < n; i++)
		//A[i] = i + 1;
	dfs(1);
	/*do {
		int ok = 1;
		for(int i=0;i<n;i++)
			if (!isp[A[i] + A[(i + 1) % n]])
			{
				ok = 0;
				break;
			}
		if (ok)
		{
			for (int i = 0; i < n; i++)
				cout << A[i] << " ";
			cout << endl;
		}
	} while (next_permutation(A + 1, A + n));*/
}
