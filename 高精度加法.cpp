#include<iostream>
#include<cmath>
using namespace std;
int main()
{
	char a[200], b[200], r, g;
	int aa[200], bb[200];
	cin >> a >> b;
	int c;
	int d = 0, e = 0, f;
	while (a[d] != '\0')
		d++;
	while (b[e] != '\0')
		e++;
	for (c = 0; c < d; c++)
	{
		aa[c] = a[c] - 48;
	}
	for (c = 0; c < e; c++)
	{
		bb[c] = b[c] - 48;
	}
	if (d > e)
	{
		int dd = d - 1;
		int ddd;
		for (c = e - 1; c >= 0; c--)
		{
			ddd = dd;
			r = 0;
			g = aa[dd] + bb[c];
			if (g>9)
			{
				while (g > 9)
				{
					r = g / 10;
					g -= 10;
					aa[ddd] = g;
					if (ddd == 0)
						cout << 1;
					aa[ddd] = g;
					g = aa[ddd - 1] + r;
					if (g < 10)
					{
						aa[ddd - 1] = g;
					}
					ddd--;
				}
			}
			else
			{
				aa[dd] = g;
			}

			dd--;
		}
		for (c = 0; c < d; c++)
			cout << aa[c];
	}
	else
	{
		int ee = e - 1;
		int eee;
		for (c = d - 1; c >= 0; c--)
		{
			eee = ee;
			r = 0;
			g = aa[c] + bb[ee];
			if (g > 9)
			{
				while (g > 9)
				{
					r = g / 10;
					g -= 10;
					if(eee==0)
						cout<<1;
					bb[eee] = g;
					g = bb[eee - 1] + r;
					if (g<10)
						bb[eee - 1] = g;
					eee--;
				}
			}
			else
				bb[ee] = g;
			ee--;
		}
		for (c = 0; c < e; c++)
			cout << bb[c];
	}
}

