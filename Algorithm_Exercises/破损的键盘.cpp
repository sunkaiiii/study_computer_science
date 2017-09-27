#define _CRT_SECURE_NO_WARNINGS
#include<cstdio>
#include<stack>
#include<iostream>
#include<string>
using namespace std;
const int maxn = 100000;
int last, cur;
char s[maxn];
int main()
{
	int next[maxn];
	while(scanf("%s",s+1)==1)
	{
		int n = strlen(s + 1);
		last = cur = 0;
		next[0] = 0;
		for(int i=1;i<=n;i++)
		{
			char ch = s[i];
			if (ch == '[')
				cur = 0;
			else if (ch == ']')
				cur = last;
			else{
				next[i] = next[cur];
				next[cur] = i;
				if (cur == last)
				{
					last = i;
				}
				cur = i;
			}
		}
		for(int i=next[0];i!=0;i=next[i])
		{
			printf("%c", s[i]);
		}
		printf("\n");
	}
}