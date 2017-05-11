#include<iostream>
#include<cstring>
using namespace std;
int aa[10002];
int aaa[10002];
int l[10000];
int r[10000];
int k[10000];
int main()
{
	int a, b, c, d, e, f, g, h, i, j, max,gg;
	cin >> a;
	memset(aa, 0, sizeof(aa));
	memset(aaa, 0, sizeof(aaa));
	for (b = 0; b < a; b++)
	{
		cin >> aa[b];
		aaa[b] = aa[b];
	}
	cin >> c;
	for (b = 0; b < c; b++)
	{
		cin >> l[b] >> r[b] >> k[b];
	}
	for (e = 0; e < c; e++)
	{
		for (b = 0; b < a; b++)
		{
			aa[b] = aaa[b];
		}
		for (i = 0; i < k[e]; i++)
		{
			g = l[e] - 1;
			g += i;
			gg = g;
			max = gg;
			h = r[e];
			for (; gg < h; gg++)
			{
				if (aa[max] < aa[gg])
				{
					max = gg;
				}
			}
			j = aa[max];
			aa[max] = aa[g];
			aa[g] = j;
		}
		cout << aa[g] << endl;
	}
}
