#include<iostream>
#include<cstring>
using namespace std;
int main()
{
	int a[100][100], b, c, d, e, f, g, h;
	memset(a, 0, sizeof(a));
	cin >> b;
	for (c = 0; c < b; c++)
		for (d = 0; d < b; d++)
			cin >> a[c][d];
	e = 0;
	for (c = 0; c < b; c++)
		for (d = 0; d < b; d++)
		{
			if (a[c][d] == 1)
			{
				for (f = 0; f < b; f++)
					if (f != d&&a[c][f] == 1)
					{
						a[c][f] = 2;
					}
				for (f = 0; f < b; f++)
				{
					if (f != c&&a[f][d] == 1)
						a[f][d] = 2;
				}
				g = c + 1;
				h = d + 1;
				for (f = 0; f < b - 1; f++)
				{
					if (g == b)
						g = 0;
					if (h == b)
						h = 0;
					if (a[g][h] == 1)
						a[g][h] = 2;
					g++;
					h++;
				}
				g = c - 1;
				h = d + 1;
				for (f = 0; f < b - 1; f++)
				{
					if (g < 0)
						g = b - 1;
					if (h == b)
						h = 0;
					if (a[g][h] == 1)
						a[g][h] = 2;
					h++;
					g--;
				}
			}
		}
	for (c = 0; c < b; c++)
		for (d = 0; d < b; d++)
		{
			if (a[c][d] == 2)
			{
				for (f = 0; f < b; f++)
					if (f != d&&a[c][f] == 2)
					{
						a[c][f] = 3;
					}
				for (f = 0; f < b; f++)
				{
					if (f != c&&a[f][d] == 2)
						a[f][d] = 3;
				}
				g = c + 1;
				h = d + 1;
				for (f = 0; f < b - 1; f++)
				{
					if (g == b)
						g = 0;
					if (h == b)
						h = 0;
					if (a[g][h] == 2)
						a[g][h] = 3;
					g++;
					h++;
				}
				g = c - 1;
				h = d + 1;
				for (f = 0; f < b - 1; f++)
				{
					if (g < 0)
						g = b - 1;
					if (h == b)
						h = 0;
					if (a[g][h] == 2)
						a[g][h] = 3;
					h++;
					g--;
				}
			}
		}
	f = 0;
	g = 0;
	for (c = 0; c < b; c++)
	{
		for (d = 0; d < b; d++)
		{
			cout << a[c][d] << " ";
			if (a[c][d] == 1)
				f++;
			if (a[c][d] == 2)
				g++;
		}
	cout << endl;
	}
	if (f == g)
		cout << f << endl;
	else
		cout << 0 << endl;
}

