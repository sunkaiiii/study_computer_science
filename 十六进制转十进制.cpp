#include<iostream>
#include<cstring> 
using namespace std;
int g[1000];
int main()
{
	long long a = 0;
	string b;
	cin >> b;
	long long c = 1;
	int d,e;
	for (d = b.length()-1; d >= 0; d--)
	{
		switch (b[d])
		{
		case '0':e = 0; break;
		case '1':e=1; break;
		case '2':e=2; break;
		case '3':e = 3; break;
		case '4':e=4; break;
		case '5':e=5; break;
		case '6':e=6; break;
		case '7':e=7; break;
		case '8':e=8; break;
		case '9':e=9; break;
		case 'A':e=10; break;
		case 'B':e=11; break;
		case 'C':e=12; break;
		case 'D':e=13; break;
		case 'E':e=14; break;
		case 'F':e=15; break;
		default:
			break;
		}
		a = a + e*c;
		//cout << a << ",";
		c *= 16;
	}
	cout << a << endl;
}
