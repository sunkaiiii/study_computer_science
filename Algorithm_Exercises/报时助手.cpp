#include<iostream>
#include<cstring>
using namespace std;
int main()
{
	char a[200][20] = { "zero","one","two","three","four","five","six","seven","eight","nine","ten","eleven","twelve","thirteen","fourteen","fifteen","sixteen","seventeen","eighteen","nineteen","twenty" };
	strcpy(a[30], "thirty");
	strcpy(a[40], "forty");
	strcpy(a[50], "fifty");
	int b, c, d, e, f;
	cin >> b >> c;
	if (c == 0)
	{
		cout << a[b] <<" "<<"o'clock"<< endl;
	}
	else
	{
		if ((b >= 0 && b <= 20) || b == 30 || b == 40 || b == 50)
			cout << a[b] << " ";
		else
		{
			d = b / 10 * 10;
			e = b % 10;
			cout << a[d] << " " << a[e] << " ";
		}
		if ((c >= 0 && c <= 20) || c == 30 || c == 40 || c == 50)
			cout << a[c] << endl;
		else
		{
			d = c / 10 * 10;
			e = c % 10;
			cout << a[d] << " " << a[e] << endl;
		}
	}
}

