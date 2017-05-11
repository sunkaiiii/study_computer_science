//N个小球，A,B轮流取球，每次取出1/3/7/8个球，拿到最后一个球的一方为输
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;
int f(int n)
{
	if (n > 1)
	{
		if (f(n - 1) == 0)
			return 1;
	}
	if (n > 3)
	{
		if (f(n - 3) == 0)
			return 1;
	}
	if (n >7)
	{
		if (f(n - 7) == 0)
			return 1;
	}
	if (n > 8)
	{
		if (f(n - 8) == 0)
			return 1;
	}
	return 0;
}
int main()
{
	if (f(2))
		cout << "赢" << endl;
	else
		cout << "输" << endl;
}