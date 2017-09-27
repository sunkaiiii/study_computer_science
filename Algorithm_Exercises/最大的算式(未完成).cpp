#include<iostream>
#include<cstring>
#include<cmath>
using namespace std;
int a[1000];
int main()
{
	long long b, c, d, e, f;
	cin >> b >> c;
	for (d = 0; d < b; d++)
	{
		cin >> a[d];
	}
	e = 0;
	int max = 0;
	for (d = 1; d < b; d++)
	{
		if (a[d] > a[max])
			max=d;
	}
	if (c == b - 1)
	{
		e = a[0];
		for (d = 1; d < b; d++)
		{
			e *= a[d];
		}
		cout<<e<<endl;
	}
	else if (c>0)
	{
		e = 0;
		for (d = 0; d <= b-c-1; d++)
		{
			if(a[d]+a[d+1]<=max&&e+a[d]>=max)
			{
				e+=a[d];
				break;
			}
			else if (e + a[d] >= a[max])
			{
				e = e + a[d];
				break;
			}
			e += a[d];
			cout<<e<<endl;
		}
		d++;	
		while (c > 0)
		{
			f = 0;
			for (; d < b; d++)
			{
				if (f + a[d] >= a[max])
				{
					if (c > 1 && d + 1 < b&&d<b-c)
					{
						f = f + a[d];
						d++;
						break;
					}
					else if(d==b-1&&f==0&&d<b-c)
					{
						f=a[d];
						d++;
						break;
					}
					else if(d==b-1&&c<=1&&d<b-c)
					{
						f+=a[d];
						d++;
						break;
					}
					else if(d==b-c)
					{
						f+=a[d];
						d++;
						break;
					}
					else
					{
						break;
					}
				}
				f += a[d];
			}		
			e = e*f;
			cout<<e<<","<<f<<","<<d<<
			endl; 
			c--;
		}
		cout << e << endl;
	}
	else
	{
		e = 0;
		for (d = 0; d<b; d++)
		{
			e += a[d];
		}
		cout << e << endl;
	}
}
