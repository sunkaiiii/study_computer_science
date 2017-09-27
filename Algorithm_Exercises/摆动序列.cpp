#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
bool a[21];
int b[21];
int n;
int ans;
void dfs(int count)
{
	if (count > n)
		return;
	for (int i = 1; i <= n; i++)
	{
		if (!a[i])
		{
			b[count] = i;
			if (count == 1)
			{
				a[i] = true;
				dfs(count + 1);
				a[i] = false;
			}
			else if (count == 2)
			{
				ans++;
				a[i] = true;
				dfs(count + 1);
				a[i] = false;
			}
			else if (count > 2)
			{
				if ((b[count - 1] > b[count - 2] && b[count] < b[count - 2]) || (b[count - 1]<b[count - 2] && b[count]>b[count - 2]))
				{
					ans++;
					a[i] = true;
					dfs(count + 1);
					a[i] = false;
				}
			}
		}
	}
}
int main()
{
	cin >> n;
	memset(a, 0, sizeof(a));
	ans = 0;
	dfs(1);
	cout << ans << endl;
}
