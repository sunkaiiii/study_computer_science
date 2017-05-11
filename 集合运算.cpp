#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
int a[100];
int b[100];
int c[100];
int main()
{
	int aa, bb, cc, d, e, f, g;
	int min;
	cin >> aa;
	for (cc = 0; cc < aa; cc++)
	{
		cin >> a[cc];
	}
	cin >> bb;
	for (cc = 0; cc < bb; cc++)
	{
		cin >> b[cc];
	}
	d = 0;
	for (cc = 0; cc < aa; cc++)
	{
		for (e = 0; e < bb; e++)
		{
			if (a[cc] == b[e])
			{
				c[d] = a[cc];
				d++;
			}
		}
	}
	for (cc = 0; cc < d; cc++)
	{
		min = cc;
		for (e = cc; e < d; e++)
		{
			if (c[min] > c[e])
				min = e;
		}
		g = c[cc];
		c[cc] = c[min];
		c[min] = g;
	}
	for (cc = 0; cc < d; cc++)
		cout << c[cc] << " ";
	cout << endl;
	memset(c, 0, sizeof(c));
	for (cc = 0; cc < aa; cc++)
	{
		c[cc] = a[cc];
	}
	d = 0;
	f = aa;
	for (e = 0; e < bb; e++)
	{
		d = 0;
		for (cc = 0; cc < f; cc++)
		{
			if (c[cc] == b[e])
			{
				d = 1;
				break;
			}
		}
		if (d != 1)
		{
			c[f] = b[e];
			f++;
		}
	}
	for (cc = 0; cc < f; cc++)
	{
		min = cc;
		for (e = cc; e < f; e++)
		{
			if (c[min] > c[e])
				min = e;
		}
		g = c[cc];
		c[cc] = c[min];
		c[min] = g;
	}
	for (cc = 0; cc < f; cc++)
	{
		cout << c[cc] << " ";
	}
	cout << endl;
	memset(c, 0, sizeof(c));
	f = 0;
	for (cc = 0; cc < aa; cc++)
	{
		d = 0;
		for (e = 0; e < bb; e++)
		{
			if (a[cc] == b[e])
			{
				d = 1;
				break;
			}
		}
		if (d != 1)
		{
			c[f] = a[cc];
			f++;
		}
	}
	for (cc = 0; cc < f; cc++)
	{
		min = cc;
		for (e = cc; e < f; e++)
		{
			if (c[min] > c[e])
				min = e;
		}
		g = c[cc];
		c[cc] = c[min];
		c[min] = g;
	}
	for (cc = 0; cc < f; cc++)
	{
		cout << c[cc] << " ";
	}
	cout << endl;
}
