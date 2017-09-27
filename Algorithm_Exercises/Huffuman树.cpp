#include<iostream>
#include<cmath>
using namespace std;
int main()
{
	int a[200];
	int b;
	cin >> b;
	int c, d, e, f = 0, g=0,ff;
	int min = 0, min2 = 0;
	for (c = 0; c < b; c++)
		cin >> a[c];
	for (d = 0; d < b - 1; d++)
	{
		f = 0;
		while (a[f] == 0)
			f++;
		min = f;
		ff=1;
		while(a[ff]==0||ff==f)
			ff++; 
		min2 = ff;
		for (c = 0; c < b; c++)
		{
			if (a[c] < a[min] && a[c] != 0)
			{
				min2 = min;
				min = c;
			}
			else if (a[c] < a[min2] && a[c] != 0&&c!=min)
				min2 = c;
		}
		a[min] = a[min] + a[min2];
		g += a[min];
		a[min2] = 0;
	}
	cout << g << endl;

}
