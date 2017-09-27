#include<iostream>
#include<cstring> 
using namespace std;
int a[10000005];
int main()
{
	int n;
	cin >> n;
	string b, c;
	for (; n > 0; n--)
	{
		c="";
		cin >> b;
		int d;
		for (d = 0; d < b.length(); d++)
		{
			switch (b[d])
			{
			case '0':c += "0000"; break;
			case '1':c += "0001"; break;
			case '2':c += "0010"; break;
			case '3':c += "0011"; break;
			case '4':c += "0100"; break;
			case '5':c += "0101"; break;
			case '6':c += "0110"; break;
			case '7':c += "0111"; break;
			case '8':c += "1000"; break;
			case '9':c += "1001"; break;
			case 'A':c += "1010"; break;
			case 'B':c += "1011"; break;
			case 'C':c += "1100"; break;
			case 'D':c += "1101"; break;
			case 'E':c += "1110"; break;
			case 'F':c += "1111"; break;
				break;
			}
		}
		if (c.length() % 3 == 1)
			c = "00"+c;
		else if (c.length() % 3 == 2)
			c = "0"+c;
		int k = 0;
		for (d = 0; d < c.length(); d = d + 3)
		{
			a[k] = (c[d] - '0') * 4 + (c[d+1] - '0') * 2 + (c[d+2] - '0') * 1;
			k++;
		}
		for (d = 0; d < k; d++)
		{
			if(d==0&&a[d]==0)
				continue;
			cout << a[d];
		}
		cout << endl;
	}
}
