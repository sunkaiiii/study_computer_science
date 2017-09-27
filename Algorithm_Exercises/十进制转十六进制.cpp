#include<iostream>
#include<cstring> 
using namespace std;
int main()
{
	int a;
	cin >> a;
	string b="";
	do
	{
		switch (a % 16)
		{
		case 0:b = '0' + b; break;
		case 1:b = '1' + b; break;
		case 2:b = '2' + b; break;
		case 3:b = '3' + b; break;
		case 4:b = '4' + b; break;
		case 5:b = '5' + b; break;
		case 6:b = '6' + b; break;
		case 7:b = '7' + b; break;
		case 8:b = '8' + b; break;
		case 9:b = '9' + b; break;
		case 10:b = 'A' + b; break;
		case 11:b = 'B' + b; break;
		case 12:b = 'C' + b; break;
		case 13:b = 'D' + b; break;
		case 14:b = 'E' + b; break;
		case 15:b = 'F' + b; break;
		default:
			break;
		}
		a /= 16;
	}while (a > 0); 
	cout << b << endl;
}
