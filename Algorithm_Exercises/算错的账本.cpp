//财务部门发现总金额不对，发现原因是账目明细少记了几笔，通过编程寻找那几笔有遗漏
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;
void f(int sum, int a[], int k,int cur_sum,int b[])
{
	if (cur_sum > sum)
		return;

	if(cur_sum == sum)
	{
		for (int i = 0; i < 5; i++)
			if (b[i] == 0)
				cout << a[i] << " ";
		cout << endl;
		return;
	}
	if (k >= 5)
		return;
	b[k] = 0;
	f(sum, a, k + 1, cur_sum,b);
	b[k] = 1;
	cur_sum += a[k];
	f(sum, a, k + 1, cur_sum,b);
	b[k] = 0;
}
int main()
{
	int a[5] = { 3,2,4,3,1 };
	int sum = 6;
	int b[1000];
	f(sum, a, 0, 0, b);
}