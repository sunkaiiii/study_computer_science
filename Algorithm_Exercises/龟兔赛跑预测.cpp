#include<iostream>
#include<cstring>
using namespace std;
int main()
{
	int v1, v2, t, s, l;
	cin >> v1 >> v2 >> t >> s >> l;
	int a, b, c, d, e1 = 0,e2;
	a = 0;
	b = 0;
	d = s;
	while (a < l&&b<l)
	{
		if (c < t)
		{
			a = a + v2;
			b = b + v1;
			c = b - a;
			e1++;
		}
		else
		{
			if (d > 0)
			{
				a += v2;
				d--;
				e1++;
			}
			else
			{
				c = b - a;
				d = s;
			}
		}
		
	}
	if (a > b)
		cout << 'T' << endl << l/v2 << endl;
	else if(a<b)
		cout << 'R' << endl << e1 << endl;
	else
		cout<<'D'<<endl<<l/v2<<endl;
}

