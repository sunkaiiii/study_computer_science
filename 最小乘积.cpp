#include<iostream>
#include<cstring>
using namespace std;
int a[10000][10000];
int main()
{
	int b, c[10000], d, e = 0, ee, f, ff, min, k, add = 0;
	cin >> b;
	for (d = 0; d < b; d++)
	{
		cin >> c[d];
		ee = e + 2;
		for (; e < ee; e++)
		{
			for (f = 0; f < c[d]; f++)
				cin >> a[e][f];
			for (f = 0; f < c[d]; f++)
			{
				min = f;
				for (ff = f; ff < c[d]; ff++)
				{
					if (a[e][ff] < a[e][min])
					{
						min = ff;
					}
				}
				k = a[e][f];
				a[e][f] = a[e][min];
				a[e][min] = k;
			}
		}
	}
	e = 0;
	for (d = 0; d < b; d++)
	{
		add = 0;
		ff = c[d];
		ff--;
		k = 0;
		for (f = 0; f < c[d]; f++)
		{
			add = add + a[e][f] * a[e + 1][ff];
			ff--;
		}
		e += 2;
		cout << add << endl;
	}
}
