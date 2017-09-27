#include<iostream>
#include<cstring> 
using namespace std;
int c[5000];
int main()
{
	int a;
	memset(c, 0, sizeof(c));
	cin >> a;
	string b;
	cin >> b;
	int d, e = 0;
	int jishu = 0, oushu = 0;
	for (d = 0; d < b.length(); d++)
	{
		c[b[d]]++;
	}
	for (d = 0; d < 5000; d++)
	{
		if (c[d] != 0)
		{
			if (c[d] % 2 == 0)
			{
				oushu++;
			}
			else
				jishu++;
		}
	}
	if (oushu == 0 || (oushu>0 && jishu>1))
		cout << "Impossible" << endl;
	else
	{
		char aa = '1';
		int buzhou = 0, j, k = 0, l;
		for (d = 0; d < 5000; d++)
		{
			if (c[d] % 2 != 0)
			{
				aa = d;
			}
		}
		for (j = 0; j < a / 2; j++)
		{
			if (b[j] == aa)
			{
				for (k = j; k < a - j - 1; k++)
				{
					if (b[a - j - 1] == b[k])
					{
						break;
					}
				}
				buzhou = buzhou + k - j;
				for (l = k; l > j; l--)
					b[l] = b[l - 1];
				b[j] = b[a - j - 1];
				cout<<b<<endl; 
			}
			else
			{
				for (k = a - j - 1; k >= j; k--)
				{
					if (b[j] == b[k])
						break;
				}
				buzhou = buzhou + a - j - 1 - k;
				for (l = k; l < a - j - 1; l++)
					b[l] = b[l + 1];
				b[a - j - 1] = b[j];
				cout<<b<<endl;
			}
		}
		cout << buzhou << endl;
		cout << b << endl;
	}
}



