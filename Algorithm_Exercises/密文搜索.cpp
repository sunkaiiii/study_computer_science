/*

标题：密文搜索

福尔摩斯从X星收到一份资料，全部是小写字母组成。
他的助手提供了另一份资料：许多长度为8的密码列表。
福尔摩斯发现，这些密码是被打乱后隐藏在先前那份资料中的。

请你编写一个程序，从第一份资料中搜索可能隐藏密码的位置。要考虑密码的所有排列可能性。

数据格式：

输入第一行：一个字符串s，全部由小写字母组成，长度小于1024*1024
紧接着一行是一个整数n,表示以下有n行密码，1<=n<=1000
紧接着是n行字符串，都是小写字母组成，长度都为8

要求输出：
一个整数, 表示每行密码的所有排列在s中匹配次数的总和。

例如：
用户输入：
aaaabbbbaabbcccc
2
aaaabbbb
abcabccc

则程序应该输出：
4

这是因为：第一个密码匹配了3次，第二个密码匹配了1次，一共4次。
*/
#include<iostream>
#include<algorithm>
using namespace std;
char a[20000], b[1000][10], c[10];
int ans;
void judge(char a[], char b[])
{
		for (int ii = 0; ii < strlen(b); ii++)
		{
			for (int i = 0; i < strlen(a); i++)
			{
				if (b[0] == a[i])
				{
					
					int i1 = i + 1;
					for (int iii = 1; iii < strlen(b); iii++)
					{
						if (b[iii] != a[i1])
							break;
						i1++;
						if (iii == strlen(b)-1)
						{
							ans++;
							return;
						}
					}
				}
			}
	}
	return;
}
int main()
{
	cin >> a;
	int bb;
	cin >> bb;
	ans = 0;
	for (int i = 0; i < bb; i++)
	{
		cin >> b[i];
		sort(b[i],b[i]+8);
	}
	for (int i = 0; i < bb; i++)
	{
		do
		{
			judge(a, b[i]);
		} while (next_permutation(b[i], b[i] + 8));
	}
	cout << ans << endl;
}