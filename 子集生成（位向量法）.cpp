#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cstring>
using namespace std;
void print_subset(int n, int*B, int cur)
{
	if (cur == n)
	{
		for (int i = 0; i < cur; i++)
			if (B[i])
				cout << i << " ";
		cout << endl;
		return;
	}
	B[cur] = 1;
	print_subset(n, B, cur + 1);
	B[cur] = 0;
	print_subset(n, B, cur + 1);
}
int main()
{
	int b[1000];
	print_subset(3, b, 0);
}