#include<iostream>
#include<cstring>
using namespace std;
int main()
{
	int a[222][222], b, c, d, e, f;
	cin >> b >> c;
	for (e = 0; e < b; e++)
		for (f = 0; f < c; f++)
			cin >> a[e][f];
	int g = 0;
	e = 0;
	f = 0;
	int aa[222][222];
	memset(aa, 0, sizeof(aa));
	e=-1;
	while (g < b*c)
	{

		while (e + 1 < b&&!aa[e + 1][f])
		{
			aa[e][f]++;
			cout << a[++e][f] << " ";	
				g++;
		}
		while (f + 1 < c&&!aa[e][f+1])
		{
			aa[e][f]++;
			cout << a[e][++f] << " ";
			g++;
		}
		while (e - 1 >= 0 && !aa[e - 1][f])
		{
			aa[e][f]++;
			cout << a[--e][f] << " ";
			g++;
		}
		while (f - 1 >= 0 && !aa[e][f-1])
		{
			aa[e][f]++;
			cout << a[e][--f] << " ";	
			g++;
		}
	}
}

