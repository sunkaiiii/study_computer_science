//一个二叉树，并输入他们的权，从左到右输出每一个垂直位置的权的和
#include<iostream>
using namespace std;
int sum[100000];
void build(int p)
{
	int v;
	cin >> v;
	if (v == -1)
		return;
	sum[p] += v;
	build(p - 1);
	build(p + 1);
}
bool init()
{
	int v;
	cin >> v;
	if (v == -1)
		return false;
	memset(sum, 0, sizeof(sum));
	int pos = 100000 / 2;
	sum[pos] = v;
	build(pos - 1);
	build(pos + 1);
}
int main()
{
	int kase = 0;
	while (init())
	{
		int p = 0;
		while (sum[p] == 0)
			p++;
		cout << "Case " << ++kase << "\n" << sum[p++];
		while (sum[p] != 0)
			cout << " " << sum[p++];
		cout << "\n\n";
	}
}