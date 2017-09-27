#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cstring>
using namespace std;
int n, tot, C[100];
void search(int cur)
{
	if (cur == n)
	{
		for (int i = 0; i < cur; i++)
			cout << C[i] << ",";
		cout << endl;
		tot++;
	}
	else
		for (int i = 0; i < n; i++)
		{
			int ok = 1;
			C[cur] = i;
			for(int j=0;j<cur;j++)
				if (C[cur] == C[j] || cur - C[cur] == j - C[j] || cur + C[cur] == j + C[j])
				{
					ok = 0;
					break;
				}
			if (ok)
				search(cur + 1);
		}
}
int main()
{
	tot = 0;
	cin >> n;
	memset(C, 0, sizeof(C));
	search(0);
	cout << tot << endl;
}
